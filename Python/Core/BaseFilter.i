
%{
#include <ATK/Core/BaseFilter.h>
%}

namespace ATK
{
  class BaseFilter
  {
  public:
    void set_input_port(int input_port, BaseFilter* filter, int output_port);
    void set_input_sampling_rate(int rate);
    void set_output_sampling_rate(int rate);
  };

}
