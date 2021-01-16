/**
 * \file ChamberlinFilter.h
 */

#ifndef ATK_EQ_CHAMBERLINFILTER_H
#define ATK_EQ_CHAMBERLINFILTER_H

#include <ATK/EQ/config.h>
#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// State filter class
  template<typename DataType_>
  class ATK_EQ_EXPORT ChamberlinFilter: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    
  private:
    CoeffDataType numerical_frequency{0};
    CoeffDataType numerical_attenuation{1};
    
    mutable CoeffDataType yh{0};
    mutable CoeffDataType yb{0};
    mutable CoeffDataType yl{0};
    
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
    void process_impl(gsl::index size) const final;

  private:
    int selected{0};
    CoeffDataType attenuation{1};
    CoeffDataType cutoff_frequency{0};
  };
}

#endif
