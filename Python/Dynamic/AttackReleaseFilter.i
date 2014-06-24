
%{
#include <ATK/Dynamic/AttackReleaseFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class AttackReleaseFilter: public BaseFilter
  {
  public:
    AttackReleaseFilter(int nb_channels);
    ~AttackReleaseFilter();

    void set_attack(DataType_ attack);
    DataType_ get_attack() const;
    void set_release(DataType_ release);
    DataType_ get_release() const;
  };
}

%template(FloatAttackReleaseFilter) ATK::AttackReleaseFilter<float>;
%template(DoubleAttackReleaseFilter) ATK::AttackReleaseFilter<double>;
