/**
 * \file GainExpanderFilter.h
 */

#ifndef ATK_DYNAMIC_GAINEXPANDERFILTER_H
#define ATK_DYNAMIC_GAINEXPANDERFILTER_H

#include <ATK/Dynamic/GainFilter.h>
#include <ATK/Dynamic/config.h>

namespace ATK
{
  /// Gain "expander". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainExpanderFilter : public ParentGainFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = ParentGainFilter<DataType_>;
    using Parent::ratio;
    using Parent::start_recomputeLUT;
    using typename Parent::DataType;
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    * @param LUTsize is the total LUT size used by the filter
    * @param LUTprecision is the number of elements used to compute values < 1
    */
    GainExpanderFilter(gsl::index nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 1024);
    /// Destructor
    ~GainExpanderFilter() override = default;

    /// Sets the softness of the knee of the filter (positive value)
    void set_softness(DataType_ softness);
    /// Retrieves the softness afctor
    DataType_ get_softness() const;

  protected:
    DataType_ computeGain(DataType_ value) const;
  private:
    DataType_ softness{0.0001};
  };
}

#endif
