/**
 * \file RobertBristowJohnsonFilter.h
 */

#ifndef ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H
#define ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H

#include <ATK/EQ/SecondOrderFilter.h>

namespace ATK
{
  template<typename DataType_>
  class RobertBristowJohnsonLowPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;
        
  public:
    RobertBristowJohnsonLowPassCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonHighPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;

  public:
    RobertBristowJohnsonHighPassCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonBandPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;

  public:
    RobertBristowJohnsonBandPassCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonBandPass2Coefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;

  public:
    RobertBristowJohnsonBandPass2Coefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonBandStopCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;

  public:
    RobertBristowJohnsonBandStopCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonAllPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;

    void setup() override;

  public:
    RobertBristowJohnsonAllPassCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonBandPassPeakCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;
    DataType gain;

    void setup() override;

  public:
    RobertBristowJohnsonBandPassPeakCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
    void set_gain(DataType_ Q);
    DataType_ get_gain() const;
  };

  template<typename DataType_>
  class RobertBristowJohnsonLowShelvingCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;
    DataType gain;

    void setup() override;

  public:
    RobertBristowJohnsonLowShelvingCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
    void set_gain(DataType_ Q);
    DataType_ get_gain() const;
};

  template<typename DataType_>
  class RobertBristowJohnsonHighShelvingCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    DataType Q;
    DataType gain;

    void setup() override;

  public:
    RobertBristowJohnsonHighShelvingCoefficients(int nb_channels = 1);

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
    void set_gain(DataType_ Q);
    DataType_ get_gain() const;
  };
}

#endif
