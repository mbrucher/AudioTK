
%{
#include <cstdint>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
%}

%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float* array, int channels, int64_t size)}
%apply (double* INPLACE_ARRAY2, int DIM1, int DIM2) {(double* array, int channels, int64_t size)}

namespace ATK
{
  template<class DataType>
  class InPointerFilter: public BaseFilter
  {
  public:
    InPointerFilter(DataType* array, int channels, int64_t size, bool interleaved);
    ~InPointerFilter();
    int get_nb_output_ports();
  };
}

%template(FloatInPointerFilter) ATK::InPointerFilter<float>;
%template(DoubleInPointerFilter) ATK::InPointerFilter<double>;

namespace ATK
{
  template<class DataType>
  class OutPointerFilter: public BaseFilter
  {
  public:
    OutPointerFilter(DataType* array, int channels, int64_t size, bool interleaved);
    ~OutPointerFilter();
    int get_nb_input_ports();
  };
}

%template(FloatOutPointerFilter) ATK::OutPointerFilter<float>;
%template(DoubleOutPointerFilter) ATK::OutPointerFilter<double>;
