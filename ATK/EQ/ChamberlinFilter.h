/**
 * \file ChamberlinFilter.h
 */

#ifndef ATK_EQ_CHAMBERLINFILTER_H
#define ATK_EQ_CHAMBERLINFILTER_H

#include "config.h"
#include "../Core/TypedBaseFilter.h"

namespace ATK
{
  /// State filter class
  template<typename DataType_>
  class ATK_EQ_EXPORT ChamberlinFilter: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
  private:
    CoeffDataType numerical_frequency;
    CoeffDataType numerical_attenuation;
    
    mutable CoeffDataType yh;
    mutable CoeffDataType yb;
    mutable CoeffDataType yl;
    
  public:
    ChamberlinFilter();
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType CoeffDataType);
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const;
    
    void set_attenuation(CoeffDataType attenuation);
    CoeffDataType get_attenuation() const;
    
    /// Select low pass, band pass or high pass output
    void select(int selected);
    int get_selected() const;
    
  protected:
    void setup() final;
    void process_impl(std::size_t size) const final;

  private:
    int selected;
    CoeffDataType attenuation;
    CoeffDataType cutoff_frequency;
  };
}

#endif
