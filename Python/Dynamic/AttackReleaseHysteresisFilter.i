
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
    void set_attack_hysteresis(DataType attack_hysteresis);
    void set_attack_hysteresis_db(DataType attack_hysteresis_db);
    DataType get_attack_hysteresis() const;
    void set_release_hysteresis(DataType release_hysteresis);
    void set_release_hysteresis_db(DataType release_hysteresis_db);
    DataType get_release_hysteresis() const;
  };
}

%template(FloatAttackHysteresisReleaseFilter) ATK::AttackReleaseHysteresisFilter<float>;
%template(DoubleAttackReleaseHysteresisFilter) ATK::AttackReleaseHysteresisFilter<double>;
