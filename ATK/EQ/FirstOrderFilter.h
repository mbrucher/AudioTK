/**
 * \file FirstOrderFilter.h
 */

#ifndef ATK_EQ_FIRSTORDERFILTER_H
#define ATK_EQ_FIRSTORDERFILTER_H

#include "config.h"
#include "../Core/TypedBaseFilter.h"

namespace ATK
{
  /**
   * First order filter template class
   */
  template<typename DataType_>
  class ATK_EQ_EXPORT FirstOrderFilter: public TypedBaseFilter<DataType_>
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
    
  private:
    DataType numerical_frequency;
    DataType numerical_attenuation;
    
    DataType yh;
    DataType yb;
    DataType yl;
    
  public:
    FirstOrderFilter();
    
    void set_cut_frequency(DataType cutoff_frequency);
    DataType get_cut_frequency() const;
    
    void set_attenuation(DataType attenuation);
    DataType get_attenuation() const;
    
    void select(int selected);
    int get_selected() const;
    
  protected:
    void setup();
    void process_impl(std::int64_t size);
    
    int selected;
    DataType attenuation;
    DataType cutoff_frequency;
  };
}

#endif
