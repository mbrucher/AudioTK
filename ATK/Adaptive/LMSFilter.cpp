/**
 * \file LMSFilter.cpp
 */

#include "LMSFilter.h"

#include <cstdint>
#include <stdexcept>

#include <Eigen/Core>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<typename DataType_>
  class LMSFilter<DataType_>::LMSFilterImpl
  {
  public:
    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, 1> wType;
    typedef Eigen::Map<const wType> xType;

    wType w;
    /// Memory factor
    DataType_ alpha;
    /// line search
    DataType_ mu;

    LMSFilterImpl(std::size_t size)
    :w(wType::Zero(size, 1)), alpha(.99), mu(0.05)
    {
    }

    void update(const xType& x, DataType error)
    {
      w = alpha * w + mu * error * x;
    }

    void update_normalized(const xType& x, DataType error)
    {
      w = alpha * w + mu * error * x / (std::numeric_limits<DataType>::epsilon() + x.squaredNorm());
    }

    void update_signerror(const xType& x, DataType error)
    {
      w = alpha * w + mu * std::copysign(1, error) * x;
    }
  };

  template<typename DataType_>
  LMSFilter<DataType_>::LMSFilter(std::size_t size)
  :Parent(2, 1), impl(new LMSFilterImpl(size)), mode(Mode::NORMAL), global_size(size)
  {
    input_delay = size + 1;
  }
  
  template<typename DataType_>
  LMSFilter<DataType_>::~LMSFilter()
  {
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::set_size(std::size_t size)
  {
    if(size == 0)
    {
      throw std::out_of_range("Size must be strictly positive");
    }

    input_delay = size+1;
    this->global_size = size;
  }

  template<typename DataType_>
  std::size_t LMSFilter<DataType_>::get_size() const
  {
    return global_size;
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::set_memory(DataType_ memory)
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
  DataType_ LMSFilter<DataType_>::get_memory() const
  {
    return impl->alpha;
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::set_mu(DataType_ mu)
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
  DataType_ LMSFilter<DataType_>::get_mu() const
  {
    return impl->mu;
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::set_mode(Mode mode)
  {
    this->mode = mode;
  }

  template<typename DataType_>
  typename LMSFilter<DataType_>::Mode LMSFilter<DataType_>::get_mode() const
  {
    return mode;
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::process_impl(std::size_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    const DataType* ATK_RESTRICT ref = converted_inputs[1];
    DataType* ATK_RESTRICT output = outputs[0];
    
    auto update_function = mode == Mode::NORMAL ? &LMSFilterImpl::update : (mode == Mode::NORMALIZED ? &LMSFilterImpl::update_normalized : &LMSFilterImpl::update_signerror);

    for(std::size_t i = 0; i < size; ++i)
    {
      typename LMSFilterImpl::xType x(input - global_size + i, global_size, 1);
      output[i] = impl->w.conjugate().dot(x);

      (impl.get()->*update_function)(x, TypeTraits<DataType>::conj(ref[i] - output[i]));
    }
  }

  template<typename DataType_>
  const DataType_* LMSFilter<DataType_>::get_w() const
  {
    return impl->w.data();
  }

  template class LMSFilter<float>;
  template class LMSFilter<double>;
}
