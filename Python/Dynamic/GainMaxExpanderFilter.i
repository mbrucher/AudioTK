
%{
#include <ATK/Dynamic/GainMaxExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainMaxExpanderFilter: public BaseFilter
  {
  public:
    GainMaxExpanderFilter(int nb_channels = 1);
    ~GainMaxExpanderFilter();

    void set_max_reduction(DataType max_reduction);
    void set_max_reduction_db(DataType max_reduction);
    DataType get_max_reduction() const;
  };

  ATKProperty(GainMaxExpanderFilter<float>, threshold, get_threshold, set_threshold);
  ATKProperty(GainMaxExpanderFilter<float>, softness, get_softness, set_softness);
  ATKProperty(GainMaxExpanderFilter<float>, max_reduction, get_max_reduction, set_max_reduction);
  ATKProperty(GainMaxExpanderFilter<double>, threshold, get_threshold, set_threshold);
  ATKProperty(GainMaxExpanderFilter<double>, softness, get_softness, set_softness);
  ATKProperty(GainMaxExpanderFilter<double>, max_reduction, get_max_reduction, set_max_reduction);
}

%template() ATK::GainMaxExpanderFilter<float>;
%template() ATK::GainMaxExpanderFilter<double>;
%template(FloatGainMaxExpanderFilter) ATK::GainFilter<ATK::GainMaxExpanderFilter<float> >;
%template(DoubleGainMaxExpanderFilter) ATK::GainFilter<ATK::GainMaxExpanderFilter<double> >;
