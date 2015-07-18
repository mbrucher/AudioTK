/**
 * \file RLSFilter.h
 */

#ifndef ATK_ADAPTIVE_RLSFILTER_H
#define ATK_ADAPTIVE_RLSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

#include <Eigen/Core>

namespace ATK
{
  /**
   * Recursive
   */
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT RLSFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::input_delay;

  public:
    RLSFilter(int64_t size);
    ~RLSFilter();
    
    void set_size(int64_t delay);
    int64_t get_size() const;

    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic> PType;
    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, 1> wType;
    
    void set_P(const Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic>& P);
    Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic> get_P() const;
    void set_w(const Eigen::Matrix<DataType_, Eigen::Dynamic, 1>& w);
    Eigen::Matrix<DataType_, Eigen::Dynamic, 1> get_w() const;

    void set_memory(DataType_ memory);
    DataType_ get_memory() const;

    void set_learning(bool learning);
    bool get_learning() const;

  protected:
    virtual void process_impl(int64_t size);
    
    typedef Eigen::Map<const wType> xType;
    
    void learn(const xType& x, DataType_ target, DataType_ actual);
    
    int64_t size;
    PType P;
    wType w;
    DataType memory;
    bool learning;
  };
}

#endif
