
%{
#include <ATK/Preamplifier/DempwolfTriodeFunction.h>
#include <ATK/Preamplifier/EnhancedKorenTriodeFunction.h>
#include <ATK/Preamplifier/KorenTriodeFunction.h>
#include <ATK/Preamplifier/LeachTriodeFunction.h>
#include <ATK/Preamplifier/MunroPiazzaTriodeFunction.h>
#include <ATK/Preamplifier/TriodeFilter.h>
%}

namespace ATK
{
  template<typename DataType>
  class LeachTriodeFunction
  {
  };

  template<typename DataType>
  class KorenTriodeFunction
  {
  };

  template<typename DataType>
  class EnhancedKorenTriodeFunction
  {
  };

  template<typename DataType, typename TubeFunction>
  class TriodeFilter: public BaseFilter
  {
  public:
    ~TriodeFilter();
  };
}

%template(FloatLeachTriodeFilter) ATK::TriodeFilter<float, ATK::LeachTriodeFunction<float> >;
%template(DoubleLeachTriodeFilter) ATK::TriodeFilter<double, ATK::LeachTriodeFunction<double> >;
%template(FloatKorenTriodeFilter) ATK::TriodeFilter<float, ATK::KorenTriodeFunction<float> >;
%template(DoubleKorenTriodeFilter) ATK::TriodeFilter<double, ATK::KorenTriodeFunction<double> >;
%template(FloatEnhancedKorenTriodeFilter) ATK::TriodeFilter<float, ATK::EnhancedKorenTriodeFunction<float> >;
%template(DoubleEnhancedKorenTriodeFilter) ATK::TriodeFilter<double, ATK::EnhancedKorenTriodeFunction<double> >;
%template(FloatMunroPiazzaTriodeFilter) ATK::TriodeFilter<float, ATK::MunroPiazzaTriodeFunction<float> >;
%template(DoubleMunroPiazzaTriodeFilter) ATK::TriodeFilter<double, ATK::MunroPiazzaTriodeFunction<double> >;
%template(FloatDempwolfTriodeFilter) ATK::TriodeFilter<float, ATK::DempwolfTriodeFunction<float> >;
%template(DoubleDempwolfTriodeFilter) ATK::TriodeFilter<double, ATK::DempwolfTriodeFunction<double> >;

PreampExtend(ATK::TriodeFilter,float, ATK::LeachTriodeFunction);
PreampExtend(ATK::TriodeFilter,double, ATK::LeachTriodeFunction);
PreampExtend(ATK::TriodeFilter,float, ATK::KorenTriodeFunction);
PreampExtend(ATK::TriodeFilter,double, ATK::KorenTriodeFunction);
PreampExtend(ATK::TriodeFilter,float, ATK::EnhancedKorenTriodeFunction);
PreampExtend(ATK::TriodeFilter,double, ATK::EnhancedKorenTriodeFunction);
PreampExtend(ATK::TriodeFilter,float, ATK::MunroPiazzaTriodeFunction);
PreampExtend(ATK::TriodeFilter,double, ATK::MunroPiazzaTriodeFunction);
PreampExtend(ATK::TriodeFilter,float, ATK::DempwolfTriodeFunction);
PreampExtend(ATK::TriodeFilter,double, ATK::DempwolfTriodeFunction);

PreampExtendAlternate(ATK::TriodeFilter,float, ATK::KorenTriodeFunction, build_alternate_function_1);
PreampExtendAlternate(ATK::TriodeFilter,double, ATK::KorenTriodeFunction, build_alternate_function_1);
PreampExtendAlternate(ATK::TriodeFilter,float, ATK::DempwolfTriodeFunction, build_alternate_function_1);
PreampExtendAlternate(ATK::TriodeFilter,double, ATK::DempwolfTriodeFunction, build_alternate_function_1);
PreampExtendAlternate(ATK::TriodeFilter,float, ATK::DempwolfTriodeFunction, build_alternate_function_2);
PreampExtendAlternate(ATK::TriodeFilter,double, ATK::DempwolfTriodeFunction, build_alternate_function_2);
