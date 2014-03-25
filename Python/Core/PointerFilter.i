
%{
#include <cstdint>
#include <ATK/Core/InPointerFilter.h>
%}

%apply (int* INPLACE_ARRAY2, int DIM1, int DIM2) {(int* array, long size, int channels)}
%apply (long long* INPLACE_ARRAY2, int DIM1, int DIM2) {(long long* array, long size, int channels)}
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float* array, long size, int channels)}
%apply (double* INPLACE_ARRAY2, int DIM1, int DIM2) {(double* array, long size, int channels)}

namespace ATK
{
  template<class DataType>
  class InPointerFilter
  {
  public:
    InPointerFilter(DataType* array, long size, int channels, bool interleaved);
    ~InPointerFilter();
    void process(long size);
    int get_nb_output_ports();
  };
}

%template(Int32InPointerFilter) ATK::InPointerFilter<int>;
%template(Int64InPointerFilter) ATK::InPointerFilter<long long>;
%template(FloatInPointerFilter) ATK::InPointerFilter<float>;
%template(DoubleInPointerFilter) ATK::InPointerFilter<double>;
