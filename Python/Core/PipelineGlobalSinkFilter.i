
%{
#include <cstdint>
#include <ATK/Core/PipelineGlobalSinkFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class PipelineGlobalSinkFilter: public BaseFilter
  {
  public:
    PipelineGlobalSinkFilter();
    ~PipelineGlobalSinkFilter();
    void add_filter(BaseFilter* filter);
    void remove_filter(BaseFilter* filter);
  };
}
