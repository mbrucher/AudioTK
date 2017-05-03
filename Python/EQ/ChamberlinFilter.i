
%{
#include <ATK/EQ/ChamberlinFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ChamberlinFilter: public BaseFilter
  {
  public:
    ChamberlinFilter();
    ~ChamberlinFilter();
    
    void set_cut_frequency(DataType cutoff_frequency);
    DataType get_cut_frequency() const;
    
    void set_attenuation(DataType attenuation);
    DataType get_attenuation() const;
    
    void select(int selected);
    int get_selected() const;
  };

  ATKProperty(ChamberlinFilter<float>, cutoff_frequency, get_cutoff_frequency, set_cutoff_frequency);
  ATKProperty(ChamberlinFilter<float>, attenuation, get_attenuation, set_attenuation);
  ATKProperty(ChamberlinFilter<float>, selected, get_selected, set_selected);
  ATKProperty(ChamberlinFilter<double>, cutoff_frequency, get_cutoff_frequency, set_cutoff_frequency);
  ATKProperty(ChamberlinFilter<double>, attenuation, get_attenuation, set_attenuation);
  ATKProperty(ChamberlinFilter<double>, selected, get_selected, set_selected);
}

%template(FloatChamberlinFilter) ATK::ChamberlinFilter<float>;
%template(DoubleChamberlinFilter) ATK::ChamberlinFilter<double>;
