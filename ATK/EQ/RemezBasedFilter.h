/**
 * \file RemezBasedFilter.h
 * From http://eeweb.poly.edu/iselesni/EL713/remez/remez.pdf
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
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using typename Parent::AlignedScalarVector;
    using Parent::input_sampling_rate;
  protected:
    /**
     * Target template that the user gave. First pair is the bandwidth, second pair is the target amplitude and the associated weight
     */
    std::vector<std::pair<std::pair<CoeffDataType, CoeffDataType>, std::pair<CoeffDataType, CoeffDataType> > > target;
    /// Oarger of the polynomial we can use
    gsl::index in_order{0};
    /// Launches the computation
    void setup() override;
    /// Final coefficients
    AlignedScalarVector coefficients_in;
    
  public:
    /// Constructor of a FIR filter using Remeze/Parks&McClellan algorithm to match a given template
    explicit RemezBasedCoefficients(gsl::index nb_channels = 1);

    /// Move constructor
    RemezBasedCoefficients(RemezBasedCoefficients&& other);

    /// Sets the template for the algorithm, pair of range of reduced frequencies + amplitude
    void set_template(const std::vector<std::pair<std::pair<CoeffDataType, CoeffDataType>, std::pair<CoeffDataType, CoeffDataType> > >& target);
    /// Retrieves the template
    const std::vector<std::pair<std::pair<CoeffDataType, CoeffDataType>, std::pair<CoeffDataType, CoeffDataType> > >& get_template() const;
    
    /// Order of the FIR filter
    void set_order(gsl::index order);
  };
}

#endif
