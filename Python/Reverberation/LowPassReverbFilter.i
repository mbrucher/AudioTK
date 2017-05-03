
%{
#include <ATK/Reverberation/LowPassReverbFilter.h>
  %}

namespace ATK
{
  template<class DataType>
  class LowPassReverbFilter: public BaseFilter
  {
  public:
    LowPassReverbFilter(int64_t max_delay);
    ~LowPassReverbFilter();
    
    void set_delay(int64_t delay);
    int64_t get_delay() const;
    
    void set_feedback(DataType feedback);
    DataType get_feedback() const;
  };

  ATKProperty(LowPassReverbFilter<float>, delay, get_delay, set_delay);
  ATKProperty(LowPassReverbFilter<float>, feedback, get_feedback, set_feedback);
  ATKProperty(LowPassReverbFilter<double>, delay, get_delay, set_delay);
  ATKProperty(LowPassReverbFilter<double>, feedback, get_feedback, set_feedback);
}

%template(FloatLowPassReverbFilter) ATK::LowPassReverbFilter<float>;
%template(DoubleLowPassReverbFilter) ATK::LowPassReverbFilter<double>;
