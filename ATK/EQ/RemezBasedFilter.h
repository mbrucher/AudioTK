/**
 * \file RemezBasedFilter.h
 * From http://eeweb.poly.edu/iselesni/EL713/remez/remez.pdf
 */

#ifndef ATK_EQ_REMEZBASEDFILTER_H
#define ATK_EQ_REMEZBASEDFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#if ATK_EIGEN == 1

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
    /// Target template that the user gave
    std::vector<std::pair<std::pair<DataType, DataType>, DataType> > target;
    /// Oarger of the polynomial we can use
    unsigned int in_order;
    /// Launches the computation
    void setup();
    /// Final coefficients
    std::vector<DataType> coefficients_in;
    
  public:
  /// Constructor of a FIR filter using Remeze/Parks&McClellan algorithm to match a given template
    RemezBasedCoefficients();
    
    /// Sets the template for the algorithm, pair of range of reduced frequencies + amplitude
    void set_template(const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& target);
    /// Retrieves the template
    const std::vector<std::pair<std::pair<DataType, DataType>, DataType> >& get_template() const;
    
    /// Order of the FIR filter
    void set_order(unsigned int order);
  };
}

#endif

#endif
