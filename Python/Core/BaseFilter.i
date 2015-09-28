
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
    int get_input_sampling_rate();
    int get_output_sampling_rate();
    
    void process(long size);
    
    void set_latency(uint64_t latency);
    uint64_t get_latency() const;
    uint64_t get_global_latency() const;

  };

}
