/**
 * \file ButterworthFilter.cpp
 */

#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/polynomial.hpp>

#include "ButterworthFilter.h"
#include "IIRFilter.h"

namespace
{
  template<typename DataType>
  void create_butterworth_analog_coefficients(int order, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    k = 1;
    z.clear(); // no zeros for this filter type
    p.clear();
    for(int i = -order+1; i < order; i += 2)
    {
      p.push_back(std::complex<DataType>(-std::cos(boost::math::constants::pi<DataType>() * i / (2 * order)), -std::sin(boost::math::constants::pi<DataType>() * i / (2 * order))));
    }
  }

  /// Transform the Wn=1 low pass analog filter in a Wn=Wn low pass filter
  template<typename DataType>
  void zpk_lp2lp(DataType Wn, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    int relative_degree = p.size() - z.size();
    
    for(int i = 0; i < z.size(); ++i)
    {
      z[i] *= Wn;
    }
    for(int i = 0; i < p.size(); ++i)
    {
      p[i] *= Wn;
    }
    
    k *= std::pow(Wn, relative_degree);
  }
  
  /// Apply a bilinear transform on z, p, k
  template<typename DataType>
  void zpk_bilinear(int fs, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    DataType fs2 = 2*fs;
    
    std::complex<DataType> f = 1;
    for(int i = 0; i < z.size(); ++i)
    {
      f *= fs2 - z[i];
    }
    for(int i = 0; i < p.size(); ++i)
    {
      f /= fs2 - p[i];
    }
    k *= f.real();

    for(int i = 0; i < z.size(); ++i)
    {
      z[i] = (fs2 + z[i]) / (fs2 - z[i]);
    }
    for(int i = 0; i < p.size(); ++i)
    {
      p[i] = (fs2 + p[i]) / (fs2 - p[i]);
    }

    z.resize(p.size(), -1);
  }

  /// Transforms the z, p, k coefficients in b, a form
  template<typename DataType>
  void zpk2ba(int fs, const std::vector<std::complex<DataType> >& z, const std::vector<std::complex<DataType> >& p, DataType k, boost::math::tools::polynomial<DataType>& b, boost::math::tools::polynomial<DataType>& a)
  {
    b = boost::math::tools::polynomial<DataType>(k);
    
    for(int i = 0; i < z.size(); ++i)
    {
      if(z[i].imag() == 0)
      {
        DataType temp[2] = {-z[i].real(), 1};
        boost::math::tools::polynomial<DataType> poly1(temp, 1);
        b *= poly1;
      }
      else if(z[i].imag() < 0)
      {
        DataType temp[3] = {z[i].real() * z[i].real() + z[i].imag() * z[i].imag(), -2 * z[i].real(), 1};
        boost::math::tools::polynomial<DataType> poly2(temp, 2);
        b *= poly2;
      }
    }

    a = boost::math::tools::polynomial<DataType>(1);
    for(int i = 0; i < p.size(); ++i)
    {
      if(p[i].imag() == 0)
      {
        DataType temp[2] = {-p[i].real(), 1};
        boost::math::tools::polynomial<DataType> poly1(temp, 1);
        a *= poly1;
      }
      else if (p[i].imag() < 0)
      {
        DataType temp[3] = {p[i].real() * p[i].real() + p[i].imag() * p[i].imag(), -2 * p[i].real(), 1};
        boost::math::tools::polynomial<DataType> poly2(temp, 2);
        a *= poly2;
      }
    }
  }
  
  template<typename DataType>
  void create_default_coeffs(int order, DataType Wn, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_butterworth_analog_coefficients(order, z, p, k);
    DataType warped = 2 * fs * std::tan(boost::math::constants::pi<DataType>() *  Wn / fs);
    zpk_lp2lp(warped, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    zpk2ba(fs, z, p, k, b, a);
    
    for(int i = 0; i < order + 1; ++i)
    {
      coefficients_in[i] = b[i];
    }
    for(int i = 0; i < order; ++i)
    {
      coefficients_out[i] = a[i];
    }
  }
}

namespace ATK
{
  template <typename DataType>
  ButterworthLowPassCoefficients<DataType>::ButterworthLowPassCoefficients()
  :Parent(1, 1), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }

  template <typename DataType>
  typename ButterworthLowPassCoefficients<DataType>::DataType ButterworthLowPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_coeffs(in_order, 2 * DataType(cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
  }

  template <typename DataType>
  ButterworthHighPassCoefficients<DataType>::ButterworthHighPassCoefficients()
  :Parent(1, 1), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType>
  typename ButterworthHighPassCoefficients<DataType>::DataType ButterworthHighPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_coeffs(in_order, (input_sampling_rate - 2 * DataType(cut_frequency)) / input_sampling_rate, coefficients_in, coefficients_out);
    for(int i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }

  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  template class ButterworthHighPassCoefficients<float>;
  template class ButterworthHighPassCoefficients<double>;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;
  template class IIRFilter<ButterworthHighPassCoefficients<float> >;
  template class IIRFilter<ButterworthHighPassCoefficients<double> >;

}
