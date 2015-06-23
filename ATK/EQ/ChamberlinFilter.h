/**
 * \file ChamberlinFilter.h
 */

#ifndef ATK_EQ_CHAMBERLINFILTER_H
#define ATK_EQ_CHAMBERLINFILTER_H

#include "config.h"
#include "../Core/TypedBaseFilter.h"

namespace ATK
{
  /**
   * First order filter template class
   */
  template<typename DataType_>
  class ATK_EQ_EXPORT ChamberlinFilter: public TypedBaseFilter<DataType_>
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
    
    mutable DataType yh;
    mutable DataType yb;
    mutable DataType yl;
    
  public:
    ChamberlinFilter();
    
    void set_cut_frequency(DataType_ cutoff_frequency);
    DataType_ get_cut_frequency() const;
    
    void set_attenuation(DataType_ attenuation);
    DataType_ get_attenuation() const;
    
    void select(int selected);
    int get_selected() const;
    
  protected:
    void setup() override final;
    void process_impl(int64_t size) const override final;
    
    int selected;
    DataType attenuation;
    DataType cutoff_frequency;
  };
}

#endif
