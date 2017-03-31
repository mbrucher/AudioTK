
%{
#include <ATK/Tools/DecimationFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class DecimationFilter: public BaseFilter
  {
  public:
    DecimationFilter(int nb_channels = 1);
    ~DecimationFilter();
  };
}

%template(Int16DecimationFilter) ATK::DecimationFilter<std::int16_t>;
%template(Int32DecimationFilter) ATK::DecimationFilter<std::int32_t>;
%template(Int64DecimationFilter) ATK::DecimationFilter<std::int64_t>;
%template(FloatDecimationFilter) ATK::DecimationFilter<float>;
%template(DoubleDecimationFilter) ATK::DecimationFilter<double>;
%template(ComplexFloatDecimationFilter) ATK::DecimationFilter<std::complex<float>>;
%template(ComplexDoubleDecimationFilter) ATK::DecimationFilter<std::complex<double>>;
