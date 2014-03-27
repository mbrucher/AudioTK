
%{
#include <ATK/Tools/OversamplingFilter.h>
%}

namespace ATK
{
  template<class DataType_>
  class Oversampling6points5order_2
  {
  };
  
  template<class DataType_>
  class Oversampling6points5order_4
  {
  };
  
  template<class DataType_>
  class Oversampling6points5order_8
  {
  };
  
  template<class DataType_>
  class Oversampling6points5order_16
  {
  };
  
  template<class DataType_>
  class Oversampling6points5order_32
  {
  };
  
  template<class DataType_, class Coefficients>
  class OversamplingFilter : public BaseFilter
  {
  public:
    OversamplingFilter();
    ~OversamplingFilter();
    virtual void process_impl(long size);
  };
}

%template(FloatOversampling6points5order_2) ATK::Oversampling6points5order_2<float>;
%template(DoubleOversampling6points5order_2) ATK::Oversampling6points5order_2<double>;
%template(FloatOversampling6points5order_4) ATK::Oversampling6points5order_4<float>;
%template(DoubleOversampling6points5order_4) ATK::Oversampling6points5order_4<double>;
%template(FloatOversampling6points5order_8) ATK::Oversampling6points5order_8<float>;
%template(DoubleOversampling6points5order_8) ATK::Oversampling6points5order_8<double>;
%template(FloatOversampling6points5order_16) ATK::Oversampling6points5order_16<float>;
%template(DoubleOversampling6points5order_16) ATK::Oversampling6points5order_16<double>;
%template(FloatOversampling6points5order_32) ATK::Oversampling6points5order_32<float>;
%template(DoubleOversampling6points5order_32) ATK::Oversampling6points5order_32<double>;

%template(FloatOversampling6points5order_2Filter) ATK::OversamplingFilter<float, ATK::Oversampling6points5order_2<float> >;
%template(DoubleOversampling6points5order_2Filter) ATK::OversamplingFilter<double, ATK::Oversampling6points5order_2<double> >;
%template(FloatOversampling6points5order_4Filter) ATK::OversamplingFilter<float, ATK::Oversampling6points5order_4<float> >;
%template(DoubleOversampling6points5order_4Filter) ATK::OversamplingFilter<double, ATK::Oversampling6points5order_4<double> >;
%template(FloatOversampling6points5order_8Filter) ATK::OversamplingFilter<float, ATK::Oversampling6points5order_8<float> >;
%template(DoubleOversampling6points5order_8Filter) ATK::OversamplingFilter<double, ATK::Oversampling6points5order_8<double> >;
%template(FloatOversampling6points5order_16Filter) ATK::OversamplingFilter<float, ATK::Oversampling6points5order_16<float> >;
%template(DoubleOversampling6points5order_16Filter) ATK::OversamplingFilter<double, ATK::Oversampling6points5order_16<double> >;
%template(FloatOversampling6points5order_32Filter) ATK::OversamplingFilter<float, ATK::Oversampling6points5order_32<float> >;
%template(DoubleOversampling6points5order_32Filter) ATK::OversamplingFilter<double, ATK::Oversampling6points5order_32<double> >;
