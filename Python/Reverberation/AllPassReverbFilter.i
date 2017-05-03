
%{
#include <ATK/Reverberation/AllPassReverbFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class AllPassReverbFilter: public BaseFilter
  {
  public:
    AllPassReverbFilter(int64_t max_delay);
    ~AllPassReverbFilter();

    void set_delay(int64_t delay);
    int64_t get_delay() const;
    
    void set_feedback(DataType feedback);
    DataType get_feedback() const;
  };

  ATKProperty(AllPassReverbFilter<float>, delay, get_delay, set_delay);
  ATKProperty(AllPassReverbFilter<float>, feedback, get_feedback, set_feedback);
  ATKProperty(AllPassReverbFilter<double>, delay, get_delay, set_delay);
  ATKProperty(AllPassReverbFilter<double>, feedback, get_feedback, set_feedback);
}

%template(FloatAllPassReverbFilter) ATK::AllPassReverbFilter<float>;
%template(DoubleAllPassReverbFilter) ATK::AllPassReverbFilter<double>;
