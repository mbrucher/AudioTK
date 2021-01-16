/**
 * \file LMSFilter.cpp
 */

#include "LMSFilter.h"
#include <ATK/Core/TypeTraits.h>
#include <ATK/Core/Utilities.h>

#include <Eigen/Core>

#include <complex>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  class LMSFilter<DataType_>::LMSFilterImpl
  {
  public:
    using wType = Eigen::Matrix<DataType_, Eigen::Dynamic, 1>;
    using xType = Eigen::Map<const wType>;

    wType w;
    /// Memory factor
    double alpha = 0.99;
    /// line search
    double mu = 0.05;

    explicit LMSFilterImpl(gsl::index size)
    :w(wType::Zero(size))
    {
    }

    using UpdateFunction = void (LMSFilterImpl::*)(const xType& x, DataType error);

    void update(const xType& x, DataType error)
    {
      w = static_cast<DataType>(alpha) * w + static_cast<DataType>(mu) * error * x;
    }

    void update_normalized(const xType& x, DataType error)
    {
      w = static_cast<DataType>(alpha) * w + static_cast<DataType>(mu) * error * x / (std::numeric_limits<DataType>::epsilon() + static_cast<DataType>(x.squaredNorm()));
    }

    void update_signerror(const xType& x, DataType error)
    {
      w = static_cast<DataType>(alpha) * w + static_cast<DataType>(mu) * error / (std::numeric_limits<DataType>::epsilon() + std::abs(error)) * x;
    }

    void update_signdata(const xType& x, DataType error)
    {
      w = static_cast<DataType>(alpha) * w.array() + static_cast<DataType>(mu) * error * x.array() / (x.cwiseAbs().template cast<DataType>().array() + static_cast<DataType>(std::numeric_limits<DataType>::epsilon()));
    }

    void update_signsign(const xType& x, DataType error)
    {
      w = static_cast<DataType>(alpha) * w.array() + static_cast<DataType>(mu) * error / (std::numeric_limits<DataType>::epsilon() + std::abs(error)) * x.array() / (x.cwiseAbs().template cast<DataType>().array() + static_cast<DataType>(std::numeric_limits<DataType>::epsilon()));
    }

    UpdateFunction select(Mode mode)
    {
      switch (mode)
      {
      case Mode::NORMAL:
        return &LMSFilterImpl::update;
      case Mode::NORMALIZED:
        return &LMSFilterImpl::update_normalized;
      case Mode::SIGNERROR:
        return &LMSFilterImpl::update_signerror;
      case Mode::SIGNDATA:
        return &LMSFilterImpl::update_signdata;
      case Mode::SIGNSIGN:
        return &LMSFilterImpl::update_signsign;
      default:
          throw std::range_error("Wrong mode for LMS filter");
      }
    }
  };

  template<typename DataType_>
  LMSFilter<DataType_>::LMSFilter(gsl::index size)
  :Parent(2, 1), impl(std::make_unique<LMSFilterImpl>(size))
  {
    input_delay = size - 1;
  }
  
  template<typename DataType_>
  LMSFilter<DataType_>::~LMSFilter()
  {
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::set_size(gsl::index size)
  {
    if(size == 0)
    {
      throw RuntimeError("Size must be strictly positive");
    }

    input_delay = size - 1;
    impl = std::make_unique<LMSFilterImpl>(size);
  }

  template<typename DataType_>
  gsl::index LMSFilter<DataType_>::get_size() const
  {
    return input_delay + 1;
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::set_memory(double memory)
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
  double LMSFilter<DataType_>::get_memory() const
  {
    return impl->alpha;
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::set_mu(double mu)
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
  double LMSFilter<DataType_>::get_mu() const
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
  void LMSFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    const DataType* ATK_RESTRICT ref = converted_inputs[1];
    DataType* ATK_RESTRICT output = outputs[0];
    
    auto update_function = impl->select(mode);

    for(gsl::index i = 0; i < size; ++i)
    {
      typename LMSFilterImpl::xType x(input - input_delay + i, input_delay + 1, 1);
      output[i] = impl->w.conjugate().dot(x);
      if(learning)
      {
        (impl.get()->*update_function)(x, TypeTraits<DataType>::conj(ref[i] - output[i]));
      }
    }
  }

  template<typename DataType_>
  const DataType_* LMSFilter<DataType_>::get_w() const
  {
    return impl->w.data();
  }
  
  template<typename DataType_>
  void LMSFilter<DataType_>::set_w(gsl::not_null<const DataType_*> w)
  {
    impl->w = Eigen::Map<const typename LMSFilterImpl::wType>(w.get(), get_size());
  }

  template<typename DataType_>
  void LMSFilter<DataType_>::set_learning(bool learning)
  {
    this->learning = learning;
  }

  template<typename DataType_>
  bool LMSFilter<DataType_>::get_learning() const
  {
    return learning;
  }

  template class LMSFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class LMSFilter<float>;
  template class LMSFilter<std::complex<float>>;
  template class LMSFilter<std::complex<double>>;
#endif
}
