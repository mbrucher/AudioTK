/**
 * \file SD1OverdriveFilter.h
 */

#ifndef ATK_DISTORTION_SD1OVERDRIVEFILTER_H
#define ATK_DISTORTION_SD1OVERDRIVEFILTER_H

#include <boost/scoped_ptr.hpp>

#include "../Core/TypedBaseFilter.h"

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
  class SD1OverdriveFilter: public TypedBaseFilter<DataType_>
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
    SD1OverdriveFilter(int nb_channels);
    ~SD1OverdriveFilter();

    void set_drive(DataType drive);

  protected:
    void setup();
    void process_impl(std::int64_t size);
    
  private:
    boost::scoped_ptr<SD1OverdriveFunction<DataType> > function;
    boost::scoped_ptr<ScalarNewtonRaphson<SD1OverdriveFunction<DataType> > > optimizer;
  };
}

#endif
