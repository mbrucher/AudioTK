
%{
#include <cstdint>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
%}

%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float* array, int channels, int64_t size)}
%apply (double* INPLACE_ARRAY2, int DIM1, int DIM2) {(double* array, int channels, int64_t size)}
%apply (std::complex<float>* INPLACE_ARRAY2, int DIM1, int DIM2) {(std::complex<float>* array, int channels, int64_t size)}
%apply (std::complex<double>* INPLACE_ARRAY2, int DIM1, int DIM2) {(std::complex<double>* array, int channels, int64_t size)}

namespace ATK
{
  template<class DataType>
  class InPointerFilter: public BaseFilter
  {
  public:
    InPointerFilter(DataType* array, int channels, int64_t size, bool interleaved);
    ~InPointerFilter();
    int get_nb_output_ports();
  };
  
  ATKgetProperty(InPointerFilter<float>, nb_output_ports, get_nb_output_ports);
  ATKgetProperty(InPointerFilter<double>, nb_output_ports, get_nb_output_ports);
  ATKgetProperty(InPointerFilter<std::complex<float>>, nb_output_ports, get_nb_output_ports);
  ATKgetProperty(InPointerFilter<std::complex<double>>, nb_output_ports, get_nb_output_ports);
}

%template(FloatInPointerFilter) ATK::InPointerFilter<float>;
%template(DoubleInPointerFilter) ATK::InPointerFilter<double>;
%template(ComplexFloatInPointerFilter) ATK::InPointerFilter<std::complex<float> >;
%template(ComplexDoubleInPointerFilter) ATK::InPointerFilter<std::complex<double> >;

namespace ATK
{
  template<class DataType>
  class OutPointerFilter: public BaseFilter
  {
  public:
    OutPointerFilter(DataType* array, int channels, int64_t size, bool interleaved);
    ~OutPointerFilter();
    int get_nb_input_ports();
  };
  
  ATKgetProperty(OutPointerFilter<float>, nb_input_ports, get_nb_input_ports);
  ATKgetProperty(OutPointerFilter<double>, nb_input_ports, get_nb_input_ports);
  ATKgetProperty(OutPointerFilter<std::complex<float>>, nb_input_ports, get_nb_input_ports);
  ATKgetProperty(OutPointerFilter<std::complex<double>>, nb_input_ports, get_nb_input_ports);
}

%template(FloatOutPointerFilter) ATK::OutPointerFilter<float>;
%template(DoubleOutPointerFilter) ATK::OutPointerFilter<double>;
%template(ComplexFloatOutPointerFilter) ATK::OutPointerFilter<std::complex<float> >;
%template(ComplexDoubleOutPointerFilter) ATK::OutPointerFilter<std::complex<double> >;
