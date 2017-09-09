/**
 * \file FourthOrderFilter.h
 */

#ifndef ATK_EQ_FOURTHORDERFILTER_H
#define ATK_EQ_FOURTHORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Base class for all IIR second order filters
  template<typename DataType_>
  class FourthOrderBaseCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType cut_frequency;

    const static int in_order=4;
    const static int out_order=4;
    AlignedScalarVector coefficients_in;
    AlignedScalarVector coefficients_out;

    void setup() override;
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    FourthOrderBaseCoefficients(std::size_t nb_channels = 1);
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
  };
}

#endif
