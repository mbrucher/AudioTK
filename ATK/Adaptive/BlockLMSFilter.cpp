/**
 * \file BlockLMSFilter.cpp
 */

#include "BlockLMSFilter.h"

#include <complex>
#include <cstdint>
#include <stdexcept>

#include <Eigen/Core>

#include <ATK/Core/TypeTraits.h>
#include <ATK/Utility/FFT.h>

namespace ATK
{
  template<typename DataType_>
  class BlockLMSFilter<DataType_>::BlockLMSFilterImpl
  {
  public:
    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, 1> wType;
    typedef Eigen::Map<const wType> xType;

    wType w;
    /// Accumulated block update
    wType accumulated_change;

    FFT<double> fft;
    /// Memory factor
    double alpha;
    /// line search
    double mu;
    /// block size
    std::size_t block_size;
    std::size_t accumulate_block_size;

    BlockLMSFilterImpl(std::size_t size)
    :w(wType::Zero(size)), accumulated_change(wType::Zero(size)), alpha(.99), mu(0.05), block_size(size), accumulate_block_size(0)
    {
      fft.set_size(2 * size);
    }

    typedef void (BlockLMSFilterImpl::*UpdateFunction)(const xType& x, DataType error);

    void apply_update()
    {
      ++accumulate_block_size;
      if (accumulate_block_size == block_size)
      {
        w = static_cast<DataType>(alpha) * w + accumulated_change;
        accumulated_change = wType::Zero(w.rows());
        accumulate_block_size = 0;
      }
    }

    void update(const xType& x, DataType error)
    {
      accumulated_change += static_cast<DataType>(mu) * error * x;
      apply_update();
    }
  };

  template<typename DataType_>
  BlockLMSFilter<DataType_>::BlockLMSFilter(std::size_t size)
  :Parent(2, 1), impl(new BlockLMSFilterImpl(size))
  {
    input_delay = size + 1;
  }
  
  template<typename DataType_>
  BlockLMSFilter<DataType_>::~BlockLMSFilter()
  {
  }
  
  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_size(std::size_t size)
  {
    if(size == 0)
    {
      throw std::out_of_range("Size must be strictly positive");
    }

    input_delay = size + 1;
    auto block_size = impl->block_size;
    impl.reset(new BlockLMSFilterImpl(size));
    set_block_size(block_size);
  }

  template<typename DataType_>
  std::size_t BlockLMSFilter<DataType_>::get_size() const
  {
    return input_delay - 1;
  }
  
  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_block_size(std::size_t size)
  {
    if (size == 0)
    {
      throw std::out_of_range("Block size must be strictly positive");
    }
    impl->accumulate_block_size = 0;
    impl->accumulated_change = BlockLMSFilterImpl::wType::Zero(size);
    impl->block_size = size;
  }

  template<typename DataType_>
  std::size_t BlockLMSFilter<DataType_>::get_block_size() const
  {
    return impl->block_size;
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_memory(double memory)
  {
    if (memory >= 1)
    {
      throw std::out_of_range("Memory must be less than 1");
    }
    if (memory <= 0)
    {
      throw std::out_of_range("Memory must be strictly positive");
    }

    impl->alpha = memory;
  }

  template<typename DataType_>
  double BlockLMSFilter<DataType_>::get_memory() const
  {
    return impl->alpha;
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_mu(double mu)
  {
    if (mu >= 1)
    {
      throw std::out_of_range("Mu must be less than 1");
    }
    if (mu <= 0)
    {
      throw std::out_of_range("Mu must be strictly positive");
    }

    impl->mu = mu;
  }

  template<typename DataType_>
  double BlockLMSFilter<DataType_>::get_mu() const
  {
    return impl->mu;
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    const DataType* ATK_RESTRICT ref = converted_inputs[1];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(std::size_t i = 0; i < size; ++i)
    {
      typename BlockLMSFilterImpl::xType x(input - input_delay - 1 + i, input_delay - 1);
      output[i] = impl->w.conjugate().dot(x);

      impl.get()->update(x, TypeTraits<DataType>::conj(ref[i] - output[i]));
    }
  }

  template<typename DataType_>
  const DataType_* BlockLMSFilter<DataType_>::get_w() const
  {
    return impl->w.data();
  }

  template class BlockLMSFilter<float>;
  template class BlockLMSFilter<double>;
  template class BlockLMSFilter<std::complex<float>>;
  template class BlockLMSFilter<std::complex<double>>;
}
