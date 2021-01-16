/**
 * \file BlockLMSFilter.cpp
 */

#include "BlockLMSFilter.h"
#include <ATK/Core/TypeTraits.h>
#include <ATK/Core/Utilities.h>
#include <ATK/Utility/FFT.h>

#include <Eigen/Core>

#include <complex>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  class BlockLMSFilter<DataType_>::BlockLMSFilterImpl
  {
  public:
    using cwType = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, 1>;
    using cxType = Eigen::Map<const cwType>;
    using wType = Eigen::Matrix<DataType_, Eigen::Dynamic, 1>;
    using xType = Eigen::Map<const wType>;

    /// FFT of the current coefficients
    cwType wfft;
    /// Current accumulated input
    std::vector<DataType_> block_input;
    /// Current accumulated ref
    std::vector<DataType_> block_ref;
    /// Current accumulated error
    std::vector<DataType_> block_error;

    /// Temporary storage
    std::vector<std::complex<double> > block_fft;
    /// Temporary storage
    std::vector<std::complex<double> > block_fft2;
    /// Temporary storage
    std::vector<DataType_> block_ifft;

    FFT<double> fft;
    /// Memory factor
    double alpha = .99;
    /// line search
    double mu = 0.05;
    /// block size
    gsl::index block_size = 0;
    gsl::index accumulate_block_size = 0;
    bool learning = true;

    explicit BlockLMSFilterImpl(gsl::index size)
    :wfft(cwType::Zero(2*size)), block_input(2 * size, DataType_(0)), block_ref(size, DataType_(0)), block_error(size, DataType_(0)),
     block_fft(2 * size), block_fft2(2 * size), block_ifft(2 * size), block_size(size)
    {
      fft.set_size(2 * size);
    }

    void apply_update()
    {
      ++accumulate_block_size;
      if (accumulate_block_size == block_size)
      {
        fft.process_forward(block_input.data(), block_fft2.data(), block_size * 2);
        for(gsl::index i = 0; i < 2 * block_size; ++i)
        {
          block_fft[i] = block_fft2[i] * wfft(i, 0) * std::complex<double>(block_size * 2); // Diagonal U * FFT factor
        }
        fft.process_backward(block_fft.data(), block_ifft.data(), block_size * 2);
        for (gsl::index i = 0; i < block_size; ++i)
        {
          block_ifft[block_size + i] = block_ref[i] - block_ifft[block_size + i]; // error on last elements of Y
          block_error[i] = block_ifft[block_size + i];
        }
        if (learning)
        {
          std::fill(block_ifft.begin(), block_ifft.begin() + block_size, 0);
          fft.process_forward(block_ifft.data(), block_fft.data(), block_size * 2); // FFT of the error stored in ifft
          for (gsl::index i = 0; i < 2 * block_size; ++i)
          {
            block_fft[i] = std::conj(block_fft2[i]) * block_fft[i] * std::complex<double>(block_size * 2); // diagonal * FFT factor
          }
          fft.process_backward(block_fft.data(), block_ifft.data(), 2 * block_size);
          fft.process_forward(block_ifft.data(), block_fft.data(), block_size);
          wfft = alpha * wfft + static_cast<std::complex<double>>(mu) * cxType(block_fft.data(), 2 * block_size);
        }

        accumulate_block_size = 0;
        std::memcpy(&block_input[0], &block_input[block_size], block_size * sizeof(DataType_));
      }
    }

    void update(DataType input, DataType ref, DataType& error)
    {
      block_input[block_size + accumulate_block_size] = input;
      error = block_ref[accumulate_block_size] - block_error[accumulate_block_size];
      block_ref[accumulate_block_size] = ref;

      apply_update();
    }
  };

  template<typename DataType_>
  BlockLMSFilter<DataType_>::BlockLMSFilter(gsl::index size)
  :Parent(2, 1), impl(std::make_unique<BlockLMSFilterImpl>(size))
  {
    if (size == 0)
    {
      throw RuntimeError("Size must be strictly positive");
    }
  }
  
  template<typename DataType_>
  BlockLMSFilter<DataType_>::~BlockLMSFilter()
  {
  }
  
  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_size(gsl::index size)
  {
    if(size == 0)
    {
      throw RuntimeError("Size must be strictly positive");
    }
    auto block_size = impl->block_size;
    impl = std::make_unique<BlockLMSFilterImpl>(size);
    set_block_size(block_size);
  }

  template<typename DataType_>
  gsl::index BlockLMSFilter<DataType_>::get_size() const
  {
    return impl->wfft.size() / 2;
  }
  
  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_block_size(gsl::index size)
  {
    if (size == 0)
    {
      throw ATK::RuntimeError("Block size must be strictly positive");
    }
    impl->accumulate_block_size = 0;
    impl->block_size = size;
    impl->block_input.assign(2 * size, 0);
    impl->block_ref.assign(size, 0);
    impl->block_fft.assign(2 * size, 0);
    impl->block_fft2.assign(2 * size, 0);
    impl->block_ifft.assign(2 * size, 0);
  }

  template<typename DataType_>
  gsl::index BlockLMSFilter<DataType_>::get_block_size() const
  {
    return impl->block_size;
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_memory(double memory)
  {
    if (memory >= 1)
    {
      throw ATK::RuntimeError("Memory must be less than 1");
    }
    if (memory <= 0)
    {
      throw ATK::RuntimeError("Memory must be strictly positive");
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
      throw ATK::RuntimeError("Mu must be less than 1");
    }
    if (mu <= 0)
    {
      throw ATK::RuntimeError("Mu must be strictly positive");
    }

    impl->mu = mu;
  }

  template<typename DataType_>
  double BlockLMSFilter<DataType_>::get_mu() const
  {
    return impl->mu;
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    const DataType* ATK_RESTRICT ref = converted_inputs[1];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(gsl::index i = 0; i < size; ++i)
    {
      impl->update(input[i], ref[i], output[i]);
    }
  }

  template<typename DataType_>
  const std::complex<double>* BlockLMSFilter<DataType_>::get_w() const
  {
    return impl->wfft.data();
  }
  
  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_w(gsl::not_null<const std::complex<double>*> w)
  {
    impl->wfft = Eigen::Map<const typename BlockLMSFilterImpl::cwType>(w.get(), get_size() * 2);
  }

  template<typename DataType_>
  void BlockLMSFilter<DataType_>::set_learning(bool learning)
  {
    impl->learning = learning;
  }

  template<typename DataType_>
  bool BlockLMSFilter<DataType_>::get_learning() const
  {
    return impl->learning;
  }

  template class BlockLMSFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class BlockLMSFilter<std::complex<double>>;
#endif
}
