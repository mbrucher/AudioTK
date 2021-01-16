/**
 * \file AttackReleaseHysteresisFilter.h
 */

#ifndef ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H
#define ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Dynamic/config.h>

namespace ATK
{
  /// Creates an output signal with the filter power of the input (computed with an AR1 with hysteresis)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT AttackReleaseHysteresisFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    explicit AttackReleaseHysteresisFilter(gsl::index nb_channels = 1);
    /// destructor
    ~AttackReleaseHysteresisFilter() override = default;

    /// Sets the speed of the attack (between 0 and 1)
    void set_attack(DataType_ attack);
    /// Gets the attack speed
    DataType_ get_attack() const;
    /// Sets the speed of the release (between 0 and 1)
    void set_release(DataType_ release);
    /// Gets the release speed
    DataType_ get_release() const;

    /// Change the attack hysteresis (must be superior to the release hysteresis)
    /*!
     * Be aware that attack hysteresis is tricky, as you can never get up to the input power...
     */
    void set_attack_hysteresis(DataType_ attack_hysteresis);
    /// Change the attack hysteresis in dB
    void set_attack_hysteresis_db(DataType_ attack_hysteresis_db);
    /// Gets the attack hysteresis factor
    DataType_ get_attack_hysteresis() const;
    /// Change the release hysteresis (between 0 and 1)
    void set_release_hysteresis(DataType_ release_hysteresis);
    /// Change the release hysteresis in dB
    void set_release_hysteresis_db(DataType_ release_hysteresis_db);
    /// Gets the release hysteresis factor
    DataType_ get_release_hysteresis() const;
    
  protected:
    void process_impl(gsl::index size) const final;
    
  private:
    DataType_ attack{1};
    DataType_ release{1};
    DataType_ attack_hysteresis{1};
    DataType_ release_hysteresis{1};
  };
}

#endif
