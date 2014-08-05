
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
}

%template(FloatChamberlinFilter) ATK::ChamberlinFilter<float>;
%template(DoubleChamberlinFilter) ATK::ChamberlinFilter<double>;
