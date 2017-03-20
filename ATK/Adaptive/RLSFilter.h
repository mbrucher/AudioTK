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
  /// RLS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT RLSFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::input_delay;

  public:
    /**
     * @brief Creates the filter with a given size
     * @param size is the size of the underlying MA filter
     */
    RLSFilter(std::size_t size);
    /// Destructor
    ~RLSFilter();
    
    /// Changes the underlying size
    void set_size(std::size_t size);
    /// Retrieve the size
    std::size_t get_size() const;

    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic> PType;
    typedef Eigen::Matrix<DataType_, Eigen::Dynamic, 1> wType;
    
    /// Sets the starting P matrix
    void set_P(const Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic>& P);
    /// Retrieves P
    Eigen::Matrix<DataType_, Eigen::Dynamic, Eigen::Dynamic> get_P() const;
    /// Sets the starting w matrix
    void set_w(const Eigen::Matrix<DataType_, Eigen::Dynamic, 1>& w);
    /// Retrieves w
    Eigen::Matrix<DataType_, Eigen::Dynamic, 1> get_w() const;

    /// Sets the memory of the RLS algorithm
    void set_memory(DataType_ memory);
    /// Retrieves the memory
    DataType_ get_memory() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;

  protected:
    virtual void process_impl(std::size_t size) const;
    
    typedef Eigen::Map<const wType> xType;
    
    /// Called to update the internal state in learning mode
    void learn(const xType& x, DataType_ target, DataType_ actual) const;
    
  private:
    std::size_t global_size;
    mutable PType P;
    mutable wType w;
    DataType memory;
    bool learning;
  };
}

#endif
