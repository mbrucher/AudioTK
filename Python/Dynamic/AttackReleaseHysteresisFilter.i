
%{
#include <ATK/Dynamic/AttackReleaseHysteresisFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class AttackReleaseHysteresisFilter: public BaseFilter
  {
  public:
    AttackReleaseHysteresisFilter(int nb_channels = 1);
    ~AttackReleaseHysteresisFilter();

    void set_attack(DataType attack);
    DataType get_attack() const;
    void set_release(DataType release);
    DataType get_release() const;
    void set_hysteresis(DataType hysteresis);
    void set_hysteresis_db(DataType hysteresis_db);
    DataType get_hysteresis() const;
  };
}

%template(FloatAttackHysteresisReleaseFilter) ATK::AttackReleaseHysteresisFilter<float>;
%template(DoubleAttackReleaseHysteresisFilter) ATK::AttackReleaseHysteresisFilter<double>;
