/**
 * \file RemezBasedFilter.h
 */

#ifndef ATK_EQ_REMEZBASEDFILTER_H
#define ATK_EQ_REMEZBASEDFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /**
   * Implementation of the Remez algorithm to compute FIR coefficients
   */
  template<typename DataType_>
  class RemezBasedCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    std::vector<std::pair<std::pair<DataType, DataType>, DataType> > target;
    
    int in_order;
    
    void setup();
    
    std::vector<DataType> coefficients_in;
    
  public:
    RemezBasedCoefficients();
    
    /// Sets the targets for the algorithm, pair of range of reduced frequencies + amplitude
    void set_target(const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target);
    const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& get_target() const;
    
    /// Order of the FIR filter
    void set_order(int order);
  };
}

#endif
