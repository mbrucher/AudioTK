
%{
#include <cstdint>
#include <ATK/Core/InPointerFilter.h>
%}

namespace ATK
{
template<class DataType>
class InPointerFilter
{
public:
  InPointerFilter(const DataType* array, long size, int channels, bool interleaved);
  ~InPointerFilter();
  void process(long size);
};
}


%apply (int* ARGOUT_ARRAY2, int DIM1, int DIM2) {(const int* array, long size, int channels)}

%template(Int32InPointerFilter) ATK::InPointerFilter<std::int32_t>;
