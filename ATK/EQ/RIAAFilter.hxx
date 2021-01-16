/**
 * \file RIAAFilter.hxx
 */

#include "RIAAFilter.h"
#include <ATK/EQ/helpers.h>

#include <boost/math/tools/polynomial.hpp>

#include <cmath>

namespace ATK
{
  template<typename DataType>
  RIAACoefficients<DataType>::RIAACoefficients(gsl::index nb_channels)
    :Parent(nb_channels)
  {
  }

  template<typename T>
  void generate_RIAA_coeffs(EQUtilities::ZPK<T>& zpk, gsl::index input_sampling_rate)
  {
    auto pi = boost::math::constants::pi<T>();
    T t1 = 1 / (input_sampling_rate * std::tan(pi / (75e-6 * input_sampling_rate)));
    T t2 = 1 / (input_sampling_rate * std::tan(pi / (318e-6 * input_sampling_rate)));
    T t3 = 1 / (input_sampling_rate * std::tan(pi / (3180e-6 * input_sampling_rate)));
    
    zpk.k = 318e-6/75e-6 * t2/(t1*t3);
    zpk.z.push_back(-1/t2);
    zpk.p.push_back(-1/t1);
    zpk.p.push_back(-1/t3);
    
    EQUtilities::zpk_bilinear(input_sampling_rate, zpk);
  }
  
  template <typename DataType>
  void RIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    EQUtilities::ZPK<CoeffDataType> zpk;

    boost::math::tools::polynomial<CoeffDataType> b{ 1 };
    boost::math::tools::polynomial<CoeffDataType> a{ 1 };

    generate_RIAA_coeffs(zpk, input_sampling_rate);
    EQUtilities::zpk2ba(zpk, b, a);
    
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
    
    EQUtilities::ZPK<CoeffDataType> zpk;
    
    boost::math::tools::polynomial<CoeffDataType> b{ 1 };
    boost::math::tools::polynomial<CoeffDataType> a{ 1 };
    
    generate_RIAA_coeffs(zpk, input_sampling_rate);
    zpk.z.back() = -.8;
    EQUtilities::zpk2ba(zpk, b, a);
    
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
