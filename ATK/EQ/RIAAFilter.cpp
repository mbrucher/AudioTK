/**
 * \file RIAAFilter.cpp
 */

#include <boost/math/tools/polynomial.hpp>

#include "helpers.h"
#include "RIAAFilter.h"
#include "IIRFilter.h"

namespace ATK
{
  template<typename DataType>
  RIAACoefficients<DataType>::RIAACoefficients(unsigned int nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType>
  void RIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    DataType t1 = 75e-6;
    DataType t2 = 318e-6;
    DataType t3 = 3180e-6;
    
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k = t2/t1;
    z.push_back(1/t2);
    z.push_back(1/t3);
    p.push_back(1/t1);

    boost::math::tools::polynomial<DataType> b({ 1 });
    boost::math::tools::polynomial<DataType> a({ 1 });
    
    zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(std::size_t(in_order + 1), b.size());
    for (size_t i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(std::size_t(in_order), a.size() - 1);
    for (size_t i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }

  template<typename DataType>
  InverseRIAACoefficients<DataType>::InverseRIAACoefficients(unsigned int nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType>
  void InverseRIAACoefficients<DataType>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);

    DataType t1 = 75e-6;
    DataType t2 = 318e-6;
    DataType t3 = 3180e-6;
    
    Parent::setup();
    
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k = t1/t2;
    p.push_back(1/t2);
    p.push_back(1/t3);
    z.push_back(1/t1);
    
    boost::math::tools::polynomial<DataType> b({ 1 });
    boost::math::tools::polynomial<DataType> a({ 1 });
    
    zpk2ba(input_sampling_rate, z, p, k, b, a);
    
    auto in_size = std::min(std::size_t(in_order + 1), b.size());
    for (size_t i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(std::size_t(in_order), a.size() - 1);
    for (size_t i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }

  template class RIAACoefficients<float>;
  template class RIAACoefficients<double>;
  template class InverseRIAACoefficients<float>;
  template class InverseRIAACoefficients<double>;
  
  template class IIRFilter<RIAACoefficients<float> >;
  template class IIRFilter<RIAACoefficients<double> >;
  template class IIRFilter<InverseRIAACoefficients<float> >;
  template class IIRFilter<InverseRIAACoefficients<double> >;
}
