
%{
#include <cstdint>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
%}

%apply (int* INPLACE_ARRAY2, int DIM1, int DIM2) {(int* array, int channels, long size)}
%apply (long long* INPLACE_ARRAY2, int DIM1, int DIM2) {(long long* array, int channels, long size)}
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float* array, int channels, long size)}
%apply (double* INPLACE_ARRAY2, int DIM1, int DIM2) {(double* array, int channels, long size)}

namespace ATK
{
  template<class DataType>
  class InPointerFilter: public BaseFilter
  {
  public:
    InPointerFilter(DataType* array, int channels, long size, bool interleaved);
    ~InPointerFilter();
    void process(long size);
    int get_nb_output_ports();
  };
}

%template(Int32InPointerFilter) ATK::InPointerFilter<int>;
%template(Int64InPointerFilter) ATK::InPointerFilter<long long>;
%template(FloatInPointerFilter) ATK::InPointerFilter<float>;
%template(DoubleInPointerFilter) ATK::InPointerFilter<double>;

namespace ATK
{
  template<class DataType>
  class OutPointerFilter: public BaseFilter
  {
  public:
    OutPointerFilter(DataType* array, int channels, long size, bool interleaved);
    ~OutPointerFilter();
    void process(long size);
    int get_nb_input_ports();
  };
}

%template(Int32OutPointerFilter) ATK::OutPointerFilter<int>;
%template(Int64OutPointerFilter) ATK::OutPointerFilter<long long>;
%template(FloatOutPointerFilter) ATK::OutPointerFilter<float>;
%template(DoubleOutPointerFilter) ATK::OutPointerFilter<double>;
