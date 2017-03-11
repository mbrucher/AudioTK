
%{
#include <ATK/Preamplifier/DempwolfTriodeFunction.h>
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/LeachTriodeFunction.h>
#include <ATK/Preamplifier/MunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/Triode2Filter.h>
%}

namespace ATK
{
  template<typename DataType, typename TubeFunction>
  class Triode2Filter: public BaseFilter
  {
  public:
    ~Triode2Filter();
  };
}

%template(FloatKorenTriode2Filter) ATK::Triode2Filter<float, ATK::KorenTriodeFunction<float> >;
%template(DoubleKorenTriode2Filter) ATK::Triode2Filter<double, ATK::KorenTriodeFunction<double>>;
%template(FloatEnhancedKorenTriode2Filter) ATK::Triode2Filter<float, ATK::EnhancedKorenTriodeFunction<float> >;
%template(DoubleEnhancedKorenTriode2Filter) ATK::Triode2Filter<double, ATK::EnhancedKorenTriodeFunction<double>>;
%template(FloatLeachTriode2Filter) ATK::Triode2Filter<float, ATK::LeachTriodeFunction<float> >;
%template(DoubleLeachTriode2Filter) ATK::Triode2Filter<double, ATK::LeachTriodeFunction<double>>;
%template(FloatMunroPiazzaTriode2Filter) ATK::Triode2Filter<float, ATK::MunroPiazzaTriodeFunction<float> >;
%template(DoubleMunroPiazzaTriode2Filter) ATK::Triode2Filter<double, ATK::MunroPiazzaTriodeFunction<double>>;
%template(FloatDempwolfTriode2Filter) ATK::Triode2Filter<float, ATK::DempwolfTriodeFunction<float> >;
%template(DoubleDempwolfTriode2Filter) ATK::Triode2Filter<double, ATK::DempwolfTriodeFunction<double>>;

PrampExtend(ATK::Triode2Filter,float, ATK::KorenTriodeFunction);
PrampExtend(ATK::Triode2Filter,double, ATK::KorenTriodeFunction);
PrampExtend(ATK::Triode2Filter,float, ATK::EnhancedKorenTriodeFunction);
PrampExtend(ATK::Triode2Filter,double, ATK::EnhancedKorenTriodeFunction);
PrampExtend(ATK::Triode2Filter,float, ATK::LeachTriodeFunction);
PrampExtend(ATK::Triode2Filter,double, ATK::LeachTriodeFunction);
PrampExtend(ATK::Triode2Filter,float, ATK::MunroPiazzaTriodeFunction);
PrampExtend(ATK::Triode2Filter,double, ATK::MunroPiazzaTriodeFunction);
PrampExtend(ATK::Triode2Filter,float, ATK::DempwolfTriodeFunction);
PrampExtend(ATK::Triode2Filter,double, ATK::DempwolfTriodeFunction);

PrampExtendAlternate(ATK::TriodeFilter,float, ATK::KorenTriodeFunction, build_alternate_function_1);
PrampExtendAlternate(ATK::TriodeFilter,double, ATK::KorenTriodeFunction, build_alternate_function_1);
PrampExtendAlternate(ATK::TriodeFilter,float, ATK::DempwolfTriodeFunction, build_alternate_function_1);
PrampExtendAlternate(ATK::TriodeFilter,double, ATK::DempwolfTriodeFunction, build_alternate_function_1);
PrampExtendAlternate(ATK::TriodeFilter,float, ATK::DempwolfTriodeFunction, build_alternate_function_2);
PrampExtendAlternate(ATK::TriodeFilter,double, ATK::DempwolfTriodeFunction, build_alternate_function_2);
