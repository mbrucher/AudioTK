
%{
#include <ATK/Reverberation/LowPassReverbFilter.h>
  %}

namespace ATK
{
  template<class DataType>
  class ApplyGainFilter: public BaseFilter
  {
  public:
    LowPassReverbFilter();
    ~LowPassReverbFilter();
    
    void set_delay(int64_t delay);
    int64_t get_delay() const;
    
    void set_feedback(DataType feedback);
    DataType get_feedback() const;
  };
}

%template(FloatLowPassReverbFilter) ATK::LowPassReverbFilter<float>;
%template(DoubleLowPassReverbFilter) ATK::LowPassReverbFilter<double>;
