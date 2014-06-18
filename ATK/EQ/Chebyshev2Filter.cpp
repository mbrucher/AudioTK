/**
 * \file Chebyshev2Filter.cpp
 */

#include <boost/math/special_functions/asinh.hpp>

#include "Chebyshev2Filter.h"
#include "IIRFilter.h"

namespace
{
  template<typename DataType>
  void create_chebyshev2_analog_coefficients(int order, DataType ripple, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    z.clear(); // no zeros for this filter type
    p.clear();
    
    DataType de = 1.0 / std::sqrt(std::pow(10, (0.1 * ripple)) - 1);
    DataType mu = boost::math::asinh(1.0 / de) / order;
    
    for(int i = -order+1; i < order; i += 2)
    {
      std::complex<DataType> p1 = -std::complex<DataType>(std::cos(i * boost::math::constants::pi<DataType>() / (2 * order)), std::sin(i * boost::math::constants::pi<DataType>() / (2 * order)));
      std::complex<DataType> p2 = std::complex<DataType>(std::sinh(mu) * p1.real(), std::cosh(mu) * p1.imag());
      
      p.push_back(std::complex<DataType>(1, 0) / p2);
      
      if(i == 0)
      {
        continue;
      }
      
      z.push_back(std::complex<DataType>(0, 1 / std::sin(i * boost::math::constants::pi<DataType>() / (2 * order))));
    }
    
    std::complex<DataType> f = 1;
    for(int i = 0; i < p.size(); ++i)
    {
      f *= - p[i];
    }
    for(int i = 0; i < z.size(); ++i)
    {
      f /= - z[i];
    }
    k = f.real();
  }
  
  template<typename DataType>
  void create_default_chebyshev2_coeffs(size_t order, DataType ripple, DataType Wn, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(order, ripple, z, p, k);
    DataType warped = 2 * fs * std::tan(boost::math::constants::pi<DataType>() *  Wn / fs);
    zpk_lp2lp(warped, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    zpk2ba(fs, z, p, k, b, a);
    
    for(size_t i = 0; i < std::min(order + 1, b.size()); ++i)
    {
      coefficients_in[i] = b[i];
    }
    for(size_t i = 0; i < std::min(order, a.size()-1); ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
  
  template<typename DataType>
  void create_bp_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(order/2, ripple, z, p, k);
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bp(std::sqrt(wc1 * wc2), wc2 - wc1, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    zpk2ba(fs, z, p, k, b, a);
    
    for(size_t i = 0; i < std::min(order + 1, b.size()); ++i)
    {
      coefficients_in[i] = b[i];
    }
    for(size_t i = 0; i < std::min(order, a.size()-1); ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
  
  template<typename DataType>
  void create_bs_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(order/2, ripple, z, p, k);
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bs(std::sqrt(wc1 * wc2), wc2 - wc1, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;
    
    zpk2ba(fs, z, p, k, b, a);
    
    for(size_t i = 0; i < std::min(order + 1, b.size()); ++i)
    {
      coefficients_in[i] = b[i];
    }
    for(size_t i = 0; i < std::min(order, a.size()-1); ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
}

namespace ATK
{
  template <typename DataType>
  Chebyshev2LowPassCoefficients<DataType>::Chebyshev2LowPassCoefficients(int nb_channels)
  :Parent(1, 1), cut_frequency(0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::set_ripple(DataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2LowPassCoefficients<DataType>::DataType Chebyshev2LowPassCoefficients<DataType>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2LowPassCoefficients<DataType>::DataType Chebyshev2LowPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2HighPassCoefficients<DataType>::Chebyshev2HighPassCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequency(0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::set_cut_frequency(DataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2HighPassCoefficients<DataType>::DataType Chebyshev2HighPassCoefficients<DataType>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::set_ripple(DataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2HighPassCoefficients<DataType>::DataType Chebyshev2HighPassCoefficients<DataType>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_chebyshev2_coeffs(in_order, ripple, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(int i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  Chebyshev2BandPassCoefficients<DataType>::Chebyshev2BandPassCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies)
  {
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::set_cut_frequencies(DataType f0, DataType f1)
  {
    this->cut_frequencies = std::make_pair(f0, f1);
    setup();
  }
  
  template <typename DataType>
  std::pair<typename Chebyshev2BandPassCoefficients<DataType>::DataType, typename Chebyshev2BandPassCoefficients<DataType>::DataType> Chebyshev2BandPassCoefficients<DataType>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::set_ripple(DataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2BandPassCoefficients<DataType>::DataType Chebyshev2BandPassCoefficients<DataType>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_bp_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2BandStopCoefficients<DataType>::Chebyshev2BandStopCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies)
  {
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::set_cut_frequencies(DataType f0, DataType f1)
  {
    this->cut_frequencies = std::make_pair(f0, f1);
    setup();
  }
  
  template <typename DataType>
  std::pair<typename Chebyshev2BandStopCoefficients<DataType>::DataType, typename Chebyshev2BandStopCoefficients<DataType>::DataType> Chebyshev2BandStopCoefficients<DataType>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::set_ripple(DataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType>
  typename Chebyshev2BandStopCoefficients<DataType>::DataType Chebyshev2BandStopCoefficients<DataType>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_bs_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template class Chebyshev2LowPassCoefficients<float>;
  template class Chebyshev2LowPassCoefficients<double>;
  template class Chebyshev2HighPassCoefficients<float>;
  template class Chebyshev2HighPassCoefficients<double>;
  template class Chebyshev2BandPassCoefficients<float>;
  template class Chebyshev2BandPassCoefficients<double>;
  template class Chebyshev2BandStopCoefficients<float>;
  template class Chebyshev2BandStopCoefficients<double>;
  
  template class IIRFilter<Chebyshev2LowPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2LowPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2HighPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<float> >;
  template class IIRFilter<Chebyshev2BandPassCoefficients<double> >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<float> >;
  template class IIRFilter<Chebyshev2BandStopCoefficients<double> >;
  
}
