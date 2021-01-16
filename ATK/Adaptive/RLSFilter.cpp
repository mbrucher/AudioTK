/**
 * \file RLSFilter.cpp
 */

#include "RLSFilter.h"
#include <ATK/Core/TypeTraits.h>
#include <ATK/Core/Utilities.h>

#include <Eigen/Core>

#include <cstdint>
#include <complex>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  class RLSFilter<DataType_>::RLSFilterImpl
  {
  public:
    using PType = Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic>;
    using wType = Eigen::Matrix<DataType_, Eigen::Dynamic, 1>;
    using xType = Eigen::Map<const wType>;

    explicit RLSFilterImpl(gsl::index size)
      :P(PType::Identity(size, size) / DataType(size)), w(wType::Zero(size))
    {
    }

    void learn(const xType& x, DataType_ target, DataType_ actual)
    {
      auto alpha = target - actual;
      auto xreverse = x.reverse();

      wType g = (P * xreverse) / ((xreverse.adjoint() * P * xreverse)(0,0) + static_cast<DataType>(memory));
      PType pupdate = (g * (xreverse.adjoint() * P));
      w = w + TypeTraits<DataType>::conj(alpha) * g;
      P = (P - (pupdate + pupdate.transpose()) / 2) * memory;
    }

    void set_P(const DataType_* P)
    {
      this->P = Eigen::Map<const PType>(P, this->P.rows(), this->P.cols());
    }

    const DataType_* get_P() const
    {
      return P.data();
    }

    void set_w(const DataType_* w)
    {
      this->w = xType(w, this->w.rows(), 1);
    }

    const DataType_* get_w() const
    {
      return w.data();
    }

    PType P;
    wType w;
    double memory = 0.99;
  };

  template<typename DataType_>
  RLSFilter<DataType_>::RLSFilter(gsl::index size)
  :Parent(1, 1), impl(std::make_unique<RLSFilterImpl>(size)), global_size(size)
  {
    input_delay = size + 1;
  }
  
  template<typename DataType_>
  RLSFilter<DataType_>::~RLSFilter()
  {
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_size(gsl::index size)
  {
    if(size == 0)
    {
      throw ATK::RuntimeError("Size must be strictly positive");
    }

    impl->P = RLSFilterImpl::PType::Identity(size, size) / DataType(size);
    impl->w = typename RLSFilterImpl::wType(size, 1);
    input_delay = size+1;
    this->global_size = size;
  }

  template<typename DataType_>
  gsl::index RLSFilter<DataType_>::get_size() const
  {
    return global_size;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_memory(double memory)
  {
    if(memory >= 1)
    {
      throw ATK::RuntimeError("Memory must be less than 1");
    }
    if(memory <= 0)
    {
      throw ATK::RuntimeError("Memory must be strictly positive");
    }
    
    impl->memory = memory;
  }
  
  template<typename DataType_>
  double RLSFilter<DataType_>::get_memory() const
  {
    return impl->memory;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_learning(bool learning)
  {
    this->learning = learning;
  }
  
  template<typename DataType_>
  bool RLSFilter<DataType_>::get_learning() const
  {
    return learning;
  }

  template<typename DataType_>
  void RLSFilter<DataType_>::process_impl(gsl::index size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(gsl::index i = 0; i < size; ++i)
    {
      typename RLSFilterImpl::xType x(input - global_size + i, global_size, 1);
      
      // compute next sample
      output[i] = impl->w.adjoint().dot(x.reverse());
      
      if(learning)
      {
        //update w and P
        impl->learn(x, input[i], output[i]);
      }
    }
  }

  template<typename DataType_>
  void RLSFilter<DataType_>::set_P(const DataType_* P)
  {
     impl->set_P(P);
  }
  
  template<typename DataType_>
  const DataType_* RLSFilter<DataType_>::get_P() const
  {
    return impl->get_P();
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_w(const DataType_* w)
  {
    impl->set_w(w);
  }
  
  template<typename DataType_>
  const DataType_* RLSFilter<DataType_>::get_w() const
  {
    return impl->get_w();
  }

  template class RLSFilter<double>;
#if ATK_ENABLE_INSTANTIATION
  template class RLSFilter<float>;
  template class RLSFilter<std::complex<float>>;
  template class RLSFilter<std::complex<double>>;
#endif
}
