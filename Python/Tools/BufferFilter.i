
%{
#include <ATK/Tools/BufferFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class BufferFilter: public BaseFilter
  {
  public:
    BufferFilter(int nb_channels = 1);
    ~BufferFilter();
  };
}

%template(Int16BufferFilter) ATK::BufferFilter<std::int16_t>;
%template(Int32BufferFilter) ATK::BufferFilter<std::int32_t>;
%template(Int64BufferFilter) ATK::BufferFilter<std::int64_t>;
%template(FloatBufferFilter) ATK::BufferFilter<float>;
%template(DoubleBufferFilter) ATK::BufferFilter<double>;
