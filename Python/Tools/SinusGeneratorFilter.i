
%{
#include <ATK/Tools/SinusGeneratorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SinusGeneratorFilter: public BaseFilter
  {
  public:
    SinusGeneratorFilter();
    ~SinusGeneratorFilter();
    
    /// Sets the frequency of the oscillator, without resetting it
    void set_frequency(DataType frequency);
    /// Gets the frequency of the oscillator
    DataType get_frequency() const;

    void set_volume(double volume);
    double get_volume();
    void set_offset(double offset);
    double get_offset();
  };
}

%template(FloatSinusGeneratorFilter) ATK::SinusGeneratorFilter<float>;
%template(DoubleSinusGeneratorFilter) ATK::SinusGeneratorFilter<double>;
