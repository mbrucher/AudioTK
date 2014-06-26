
%{
#include <ATK/Dynamic/AttackReleaseFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class AttackReleaseFilter: public BaseFilter
  {
  public:
    AttackReleaseFilter(int nb_channels = 1);
    ~AttackReleaseFilter();

    void set_attack(DataType attack);
    DataType get_attack() const;
    void set_release(DataType release);
    DataType get_release() const;
  };
}

%template(FloatAttackReleaseFilter) ATK::AttackReleaseFilter<float>;
%template(DoubleAttackReleaseFilter) ATK::AttackReleaseFilter<double>;
