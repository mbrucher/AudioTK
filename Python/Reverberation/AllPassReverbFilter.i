
%{
#include <ATK/Reverberation/AllPassReverbFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ApplyGainFilter: public BaseFilter
  {
  public:
    AllPassReverbFilter();
    ~AllPassReverbFilter();

    void set_delay(int64_t delay);
    int64_t get_delay() const;
    
    void set_feedback(DataType feedback);
    DataType get_feedback() const;
  };
}

%template(FloatAllPassReverbFilter) ATK::AllPassReverbFilter<float>;
%template(DoubleAllPassReverbFilter) ATK::AllPassReverbFilter<double>;
