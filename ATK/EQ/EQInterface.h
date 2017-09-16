/**
 * \file EQInterface.h
 */

#ifndef ATK_EQ_EQINTERFACE_H
#define ATK_EQ_EQINTERFACE_H

#include <map>

namespace ATK
{
  /// Interface for a single cut frequency filter
  template<typename DataType>
  class SingleCutFrequencyInterface
  {
  public:
    virtual ~SingleCutFrequencyInterface();
    /// Sets the cut or central frequency of the filter
    virtual void set_cut_frequency(DataType cut_frequency) = 0;
    /// Returns the cut or central frequency
    virtual DataType get_cut_frequency() const = 0;
  };

  /// Interface for a dual cut frequency filter
  template<typename DataType>
  class DualCutFrequencyInterface
  {
  public:
    virtual ~DualCutFrequencyInterface();
    /// Sets the bandwidth as a bandwidth
    virtual void set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies) = 0;
    /// Sets the bandwidth as two separate values
    virtual void set_cut_frequencies(DataType f0, DataType f1) = 0;
    /// Gets the bandwidth
    virtual std::pair<DataType, DataType> get_cut_frequencies() const = 0;
  };

  /// Interface for filter with a Q parameter
  template<typename DataType>
  class QInterface
  {
  public:
    virtual ~QInterface();
    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    virtual void set_Q(DataType Q) = 0;
    /// Returns the Q factor
    virtual DataType get_Q() const = 0;
  };
  
  /// Interface for filter with a gain parameter
  template<typename DataType>
  class GainInterface
  {
  public:
    virtual ~GainInterface();
    /// Sets the gain of the filter
    virtual void set_gain(DataType gain) = 0;
    /// Returns the gain for the filter
    virtual DataType get_gain() const = 0;
  };
  
  /// Interface for filter with a ripple parameter
  template<typename DataType>
  class RippleInterface
  {
  public:
    virtual ~RippleInterface();
    /// Sets the ripple
    virtual void set_ripple(DataType ripple) = 0;
    /// Returns the ripple
    virtual DataType get_ripple() const = 0;
  };
}

#endif
