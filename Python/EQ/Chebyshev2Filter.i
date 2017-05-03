
%{
#include <ATK/EQ/Chebyshev2Filter.h>
%}

namespace ATK
{
  template<class DataType>
  class Chebyshev2LowPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev2LowPassCoefficients();
    ~Chebyshev2LowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class Chebyshev2HighPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev2HighPassCoefficients();
    ~Chebyshev2HighPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };

  template<class DataType>
  class Chebyshev2BandPassCoefficients: public BaseFilter
  {
  public:
    Chebyshev2BandPassCoefficients();
    ~Chebyshev2BandPassCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };
  
  template<class DataType>
  class Chebyshev2BandStopCoefficients: public BaseFilter
  {
  public:
    Chebyshev2BandStopCoefficients();
    ~Chebyshev2BandStopCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    void set_ripple(DataType ripple);
    DataType get_ripple() const;

    void set_order(int order);
  };

  ATKProperty(IIRFilter<Chebyshev2LowPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<Chebyshev2LowPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2LowPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<Chebyshev2LowPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2HighPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<Chebyshev2HighPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2HighPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<Chebyshev2HighPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2BandPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2BandPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2BandStopCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<Chebyshev2BandStopCoefficients<double> >, ripple, get_ripple, set_ripple);
}

%template(FloatChebyshev2LowPassCoefficients) ATK::Chebyshev2LowPassCoefficients<float>;
%template(DoubleChebyshev2LowPassCoefficients) ATK::Chebyshev2LowPassCoefficients<double>;
%template(FloatChebyshev2HighPassCoefficients) ATK::Chebyshev2HighPassCoefficients<float>;
%template(DoubleChebyshev2HighPassCoefficients) ATK::Chebyshev2HighPassCoefficients<double>;
%template(FloatChebyshev2BandPassCoefficients) ATK::Chebyshev2BandPassCoefficients<float>;
%template(DoubleChebyshev2BandPassCoefficients) ATK::Chebyshev2BandPassCoefficients<double>;
%template(FloatChebyshev2BandStopCoefficients) ATK::Chebyshev2BandStopCoefficients<float>;
%template(DoubleChebyshev2BandPStopCoefficients) ATK::Chebyshev2BandStopCoefficients<double>;

%template(FloatChebyshev2LowPassFilter) ATK::IIRFilter<ATK::Chebyshev2LowPassCoefficients<float> >;
%template(DoubleChebyshev2LowPassFilter) ATK::IIRFilter<ATK::Chebyshev2LowPassCoefficients<double> >;
%template(FloatChebyshev2HighPassFilter) ATK::IIRFilter<ATK::Chebyshev2HighPassCoefficients<float> >;
%template(DoubleChebyshev2HighPassFilter) ATK::IIRFilter<ATK::Chebyshev2HighPassCoefficients<double> >;
%template(FloatChebyshev2BandPassFilter) ATK::IIRFilter<ATK::Chebyshev2BandPassCoefficients<float> >;
%template(DoubleChebyshev2BandPassFilter) ATK::IIRFilter<ATK::Chebyshev2BandPassCoefficients<double> >;
%template(FloatChebyshev2BandStopFilter) ATK::IIRFilter<ATK::Chebyshev2BandStopCoefficients<float> >;
%template(DoubleChebyshev2BandStopFilter) ATK::IIRFilter<ATK::Chebyshev2BandStopCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2LowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2LowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2HighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2HighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2BandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2BandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2BandStopCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::Chebyshev2BandStopCoefficients<double> >, double);
