/**
 * \file SD1OverdriveFilter.h
 */

#ifndef ATK_DISTORTION_SD1OVERDRIVEFILTER_H
#define ATK_DISTORTION_SD1OVERDRIVEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Distortion/config.h>

#include <memory>

namespace ATK
{
  template<typename Function, int max_iterations, bool check_convergence>
  class ScalarNewtonRaphson;

  /// SD1 filter, based on a trapezoidal rule
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT SD1OverdriveFilter final : public TypedBaseFilter<DataType_>
  {
    class SD1OverdriveFunction;
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

    using Parent::input_delay;
    using Parent::output_delay;
  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    SD1OverdriveFilter();
    /// Destructor
    ~SD1OverdriveFilter();

    void set_drive(DataType_ drive);
    DataType_ get_drive() const;

  protected:
    void setup() final;
    void process_impl(gsl::index size) const final;
    DataType drive = 0.5;
    
  private:
    static const int num_iterations = 30;
    std::unique_ptr<ScalarNewtonRaphson<SD1OverdriveFunction, num_iterations, true> > optimizer;
  };
}

#endif
