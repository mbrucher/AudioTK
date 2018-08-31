/**
 * \file RIAAFilter.hxx
 */

#include <cmath>

#include <boost/math/tools/polynomial.hpp>

#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/helpers.h>

namespace ATK
{
  template<typename DataType>
  RIAACoefficients<DataType>::RIAACoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template<typename T1, typename T2>
  void generate_RIAA_coeffs(T1& k, T2& p, T2& z, gsl::index input_sampling_rate)
  {
    auto pi = boost::math::constants::pi<T1>();
    T1 t1 = 1 / (input_sampling_rate * std::tan(pi / (75e-6 * input_sampling_rate)));
    T1 t2 = 1 / (input_sampling_rate * std::tan(pi / (318e-6 * input_sampling_rate)));
    T1 t3 = 1 / (input_sampling_rate * std::tan(pi / (3180e-6 * input_sampling_rate)));
    
    k = 318e-6/75e-6 * t2/(t1*t3);
    z.push_back(-1/t2);
    p.push_back(-1/t1);
    p.push_back(-1/t3);
    
    EQUtilities::zpk_bilinear(input_sampling_rate, z, p, k);
  }
  
  template <typename DataType>
  void RIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    std::vector<std::complex<CoeffDataType> > z;
    std::vector<std::complex<CoeffDataType> > p;
    CoeffDataType k;

    boost::math::tools::polynomial<CoeffDataType> b{ 1 };
    boost::math::tools::polynomial<CoeffDataType> a{ 1 };

    generate_RIAA_coeffs(k, p, z, input_sampling_rate);
    EQUtilities::zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(in_order + 1, static_cast<gsl::index>(b.size()));
    for (gsl::index i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(out_order, static_cast<gsl::index>(a.size() - 1));
    for (gsl::index i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }

  template<typename DataType>
  InverseRIAACoefficients<DataType>::InverseRIAACoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template <typename DataType>
  void InverseRIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    std::vector<std::complex<CoeffDataType> > z;
    std::vector<std::complex<CoeffDataType> > p;
    CoeffDataType k;
    
    boost::math::tools::polynomial<CoeffDataType> b{ 1 };
    boost::math::tools::polynomial<CoeffDataType> a{ 1 };
    
    generate_RIAA_coeffs(k, p, z, input_sampling_rate);
    z.back() = -.8;
    EQUtilities::zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(in_order + 1, static_cast<gsl::index>(a.size()));
    for (gsl::index i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = a[i] / b[b.size() - 1];
    }
    auto out_size = std::min(out_order, static_cast<gsl::index>(b.size() - 1));
    for (gsl::index i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -b[i] / b[b.size() - 1];
    }
  }
}
