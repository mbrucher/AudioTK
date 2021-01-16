/**
 * \file RLSFilter.h
 * From Adaptive Filter Theory, Haykin
 */

#ifndef ATK_ADAPTIVE_RLSFILTER_H
#define ATK_ADAPTIVE_RLSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Adaptive/config.h>

namespace ATK
{
  /// RLS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT RLSFilter final : public TypedBaseFilter<DataType_>
  {
    class RLSFilterImpl;
    std::unique_ptr<RLSFilterImpl> impl;
  protected:
    using Parent = TypedBaseFilter<DataType_>;
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
    explicit RLSFilter(gsl::index size);
    /// Destructor
    ~RLSFilter() override;
    
    /// Changes the underlying size
    void set_size(gsl::index size);
    /// Retrieve the size
    gsl::index get_size() const;

    /// Sets the starting P matrix
    void set_P(const DataType_* P);
    /// Retrieves P
    const DataType_* get_P() const;
    /// Sets the starting w matrix
    void set_w(const DataType_* w);
    /// Retrieves w
    const DataType_* get_w() const;

    /// Sets the memory of the RLS algorithm
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;

  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    gsl::index global_size{0};
    bool learning = true;
  };
}

#endif
