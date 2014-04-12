
%{
#include <ATK/EQ/Chebyshev1Filter.h>
%}

namespace ATK
{
  template<class DataType>
  class Chebyshev1LowPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev1LowPassCoefficients();
    ~Chebyshev1LowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class Chebyshev1HighPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev1HighPassCoefficients();
    ~Chebyshev1HighPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };

  template<class DataType>
  class Chebyshev1BandPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev1BandPassCoefficients();
    ~Chebyshev1BandPassCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };
  
  template<class DataType>
  class Chebyshev1BandStopCoefficients: public BaseFilter
  {
  public:
    Chebyshev1BandStopCoefficients();
    ~Chebyshev1BandStopCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };
}

%template(FloatChebyshev1LowPassCoefficients) ATK::Chebyshev1LowPassCoefficients<float>;
%template(DoubleChebyshev1LowPassCoefficients) ATK::Chebyshev1LowPassCoefficients<double>;
%template(FloatChebyshev1HighPassCoefficients) ATK::Chebyshev1HighPassCoefficients<float>;
%template(DoubleChebyshev1HighPassCoefficients) ATK::Chebyshev1HighPassCoefficients<double>;
%template(FloatChebyshev1BandPassCoefficients) ATK::Chebyshev1BandPassCoefficients<float>;
%template(DoubleChebyshev1BandPassCoefficients) ATK::Chebyshev1BandPassCoefficients<double>;
%template(FloatChebyshev1BandStopCoefficients) ATK::Chebyshev1BandStopCoefficients<float>;
%template(DoubleChebyshev1BandPStopCoefficients) ATK::Chebyshev1BandStopCoefficients<double>;

%template(FloatChebyshev1LowPassFilter) ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<float> >;
%template(DoubleChebyshev1LowPassFilter) ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> >;
%template(FloatChebyshev1HighPassFilter) ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<float> >;
%template(DoubleChebyshev1HighPassFilter) ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> >;
%template(FloatChebyshev1BandPassFilter) ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<float> >;
%template(DoubleChebyshev1BandPassFilter) ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> >;
%template(FloatChebyshev1BandStopFilter) ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<float> >;
%template(DoubleChebyshev1BandStopFilter) ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1LowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1HighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1BandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev1BandStopCoefficients<double> >, double);
