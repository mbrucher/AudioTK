/**
 * \file RLSFilter.cpp
 */

#include "RLSFilter.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  RLSFilter<DataType_>::RLSFilter(int64_t size)
  :Parent(1, 1), global_size(size), P(PType::Identity(size, size)/size), w(wType::Zero(size, 1)), memory(.99), learning(false)
  {
    input_delay = size;
  }
  
  template<typename DataType_>
  RLSFilter<DataType_>::~RLSFilter()
  {
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_size(int64_t size)
  {
    if(size < 0)
    {
      throw std::out_of_range("Size must be positive");
    }

    P = PType::Identity(size, size) / size;
    w = wType(size, 1);
    input_delay = size+1;
    this->global_size = size;
  }

  template<typename DataType_>
  int64_t RLSFilter<DataType_>::get_size() const
  {
    return global_size;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_memory(DataType_ memory)
  {
    if(memory > 1)
    {
      throw std::out_of_range("Memory must be less than 1");
    }
    if(memory <= 0)
    {
      throw std::out_of_range("Memory must be strictly positive");
    }
    
    this->memory = memory;
  }
  
  template<typename DataType_>
  DataType_ RLSFilter<DataType_>::get_memory() const
  {
    return memory;
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
  void RLSFilter<DataType_>::process_impl(int64_t size) const
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(int64_t i = 0; i < size; ++i)
    {
      xType x(input - global_size + i, global_size, 1);
      
      // compute next sample
      output[i] = w.transpose() * x.reverse();
      
      if(learning)
      {
        //update w and P
        learn(x, input[i], output[i]);
      }
    }
  }

  template<typename DataType_>
  void RLSFilter<DataType_>::learn(const xType& x, DataType_ target, DataType_ actual) const
  {
    auto alpha = target - actual;
    auto xreverse = x.reverse();
    
    wType g = (P * xreverse) / (memory + xreverse.transpose() * P * xreverse);
    PType pupdate = (g * (xreverse.transpose() * P));
    P = (P - (pupdate+pupdate.transpose())/2) / memory;
    w = w + alpha * g;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_P(const Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic>& P)
  {
    assert(P.rows() == P.cols());
    assert(P.rows() == global_size);
    this->P = P;
  }
  
  template<typename DataType_>
  Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic> RLSFilter<DataType_>::get_P() const
  {
    return P;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_w(const Eigen::Matrix<DataType_, Eigen::Dynamic, 1>& w)
  {
    assert(w.rows() == global_size);
    this->w = w;
  }
  
  template<typename DataType_>
  Eigen::Matrix<DataType_, Eigen::Dynamic, 1> RLSFilter<DataType_>::get_w() const
  {
    return w;
  }

  template class RLSFilter<float>;
  template class RLSFilter<double>;
}
