
%{
#include <ATK/EQ/FirstOrderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class FirstOrderFilter: public BaseFilter
  {
  public:
    FirstOrderFilter();
    ~FirstOrderFilter();
    
    void set_cut_frequency(DataType cutoff_frequency);
    DataType get_cut_frequency() const;
    
    void set_attenuation(DataType attenuation);
    DataType get_attenuation() const;
    
    void select(int selected);
    int get_selected() const;
  };
}

%template(FloatFirstOrderFilter) ATK::FirstOrderFilter<float>;
%template(DoubleFirstOrderFilter) ATK::FirstOrderFilter<double>;
