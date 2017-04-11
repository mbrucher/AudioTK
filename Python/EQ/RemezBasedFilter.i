
%{
#include <ATK/EQ/RemezBasedFilter.h>
%}

%include <std_vector.i>

namespace ATK
{
  template<class DataType>
  class RemezBasedCoefficients: public BaseFilter
  {
  public:
    RemezBasedCoefficients(int channels = 1);
    ~RemezBasedCoefficients();

    void set_template(const std::vector<std::pair<std::pair<DataType, DataType>, std::pair<DataType, DataType> > >& target);
    const std::vector<std::pair<std::pair<DataType, DataType>, std::pair<DataType, DataType> > >& get_template() const;
    void set_order(unsigned int order);
  };
}

%template(DoubleRemezBasedCoefficients) ATK::RemezBasedCoefficients<double>;

%template(DoubleRemezBasedFilter) ATK::FIRFilter<ATK::RemezBasedCoefficients<double> >;

FIRFilterExtend(ATK::FIRFilter<ATK::RemezBasedCoefficients<double> >, double);
