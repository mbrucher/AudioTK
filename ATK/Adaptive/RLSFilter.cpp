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
  :Parent(1, 1), size(size), P(PType::Identity(size, size)), w(size, 1), memory(.99), learn(true)
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
    input_delay = size;
    this->size = size;
  }

  template<typename DataType_>
  int64_t RLSFilter<DataType_>::get_size() const
  {
    return size;
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_memory(DataType_ memory)
  {
    if(memory >= 1)
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
  void RLSFilter<DataType_>::set_learn(bool learn)
  {
    this->learn = learn;
  }
  
  template<typename DataType_>
  bool RLSFilter<DataType_>::get_learn() const
  {
    return learn;
  }

  template<typename DataType_>
  void RLSFilter<DataType_>::process_impl(int64_t size)
  {
    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output = outputs[0];
    
    for(int64_t i = 0; i < size; ++i)
    {
      // compute next sample
      if(learn)
      {
        //update w and P
      }
    }
  }
  
  template<typename DataType_>
  void RLSFilter<DataType_>::set_P(const Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic>& P)
  {
    assert(P.rows() == P.cols());
    assert(P.rows() == size);
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
    assert(w.rows() == size);
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
