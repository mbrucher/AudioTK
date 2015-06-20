/**
 * \file SD1OverdriveFilter.h
 */

#ifndef ATK_DISTORTION_SD1OVERDRIVEFILTER_H
#define ATK_DISTORTION_SD1OVERDRIVEFILTER_H

#include <boost/scoped_ptr.hpp>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  template<typename Function>
  class ScalarNewtonRaphson;

  template<typename DataType>
  class SD1OverdriveFunction;
  
  /**
   * First order filter template class
   */
  template<typename DataType_>
  class ATK_DISTORTION_EXPORT SD1OverdriveFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    SD1OverdriveFilter(int nb_channels = 1);
    ~SD1OverdriveFilter();

    void set_drive(DataType drive);

  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    DataType drive;
    
  private:
    boost::scoped_ptr<SD1OverdriveFunction<DataType> > function;
    boost::scoped_ptr<ScalarNewtonRaphson<SD1OverdriveFunction<DataType> > > optimizer;
  };
}

#endif
