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
  RIAACoefficients<DataType>::RIAACoefficients(std::size_t nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType>
  void RIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    auto pi = boost::math::constants::pi<CoeffDataType>();
    CoeffDataType t1 = 1 / (input_sampling_rate * std::tan(pi / (75e-6 * input_sampling_rate)));
    CoeffDataType t2 = 1 / (input_sampling_rate * std::tan(pi / (318e-6 * input_sampling_rate)));
    CoeffDataType t3 = 1 / (input_sampling_rate * std::tan(pi / (3180e-6 * input_sampling_rate)));
    
    std::vector<std::complex<CoeffDataType> > z;
    std::vector<std::complex<CoeffDataType> > p;
    CoeffDataType k = 318e-6/75e-6 * t2/(t1*t3);
    z.push_back(-1/t2);
    p.push_back(-1/t1);
    p.push_back(-1/t3);

    boost::math::tools::polynomial<CoeffDataType> b({ 1 });
    boost::math::tools::polynomial<CoeffDataType> a({ 1 });
    
    zpk_bilinear(input_sampling_rate, z, p, k);
    zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(std::size_t(in_order + 1), b.size());
    for (gsl::index i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(std::size_t(in_order), a.size() - 1);
    for (gsl::index i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }

  template<typename DataType>
  InverseRIAACoefficients<DataType>::InverseRIAACoefficients(std::size_t nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType>
  void InverseRIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    auto pi = boost::math::constants::pi<CoeffDataType>();
    CoeffDataType t1 = 1 / (input_sampling_rate * std::tan(pi / (75e-6 * input_sampling_rate)));
    CoeffDataType t2 = 1 / (input_sampling_rate * std::tan(pi / (318e-6 * input_sampling_rate)));
    CoeffDataType t3 = 1 / (input_sampling_rate * std::tan(pi / (3180e-6 * input_sampling_rate)));
    
    std::vector<std::complex<CoeffDataType> > z;
    std::vector<std::complex<CoeffDataType> > p;
    CoeffDataType k = 318e-6 / 75e-6 * t2 / (t1*t3);
    z.push_back(-1 / t2);
    p.push_back(-1 / t1);
    p.push_back(-1 / t3);

    boost::math::tools::polynomial<CoeffDataType> b({ 1 });
    boost::math::tools::polynomial<CoeffDataType> a({ 1 });
    
    zpk_bilinear(input_sampling_rate, z, p, k);
    z.back() = -.8;
    zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(std::size_t(in_order + 1), a.size());
    for (gsl::index i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = a[i] / b[b.size() - 1];
    }
    auto out_size = std::min(std::size_t(in_order), b.size() - 1);
    for (gsl::index i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -b[i] / b[b.size() - 1];
    }
  }
}
