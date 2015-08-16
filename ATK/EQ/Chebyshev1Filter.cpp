/**
 * \file Chebyshev1Filter.cpp
 */

#include <boost/math/special_functions/asinh.hpp>

#include "Chebyshev1Filter.h"
#include "helpers.h"
#include "IIRFilter.h"

namespace
{
  template<typename DataType>
  void create_chebyshev1_analog_coefficients(int order, DataType ripple, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    z.clear(); // no zeros for this filter type
    p.clear();
    if(ripple == 0)
    {
      return;
    }
    if(order == 0)
    {
      k = static_cast<DataType>(std::pow(10, (-ripple / 20)));
      return;
    }
    
    DataType eps = static_cast<DataType>(std::sqrt(std::pow(10, (0.1 * ripple)) - 1.0));
    DataType mu = static_cast<DataType>(1.0 / order * boost::math::asinh(1 / eps));
    
    for(int i = -order+1; i < order; i += 2)
    {
      DataType theta = boost::math::constants::pi<DataType>() * i / (2*order);
      p.push_back(-std::sinh(std::complex<DataType>(mu, theta)));
    }

    std::complex<DataType> f = 1;
    
    for(int i = 0; i < p.size(); ++i)
    {
      f *= -p[i];
    }
    k = f.real();
    if(order % 2 == 0)
    {
      k = k / std::sqrt((1 + eps * eps));
    }
  }
  
  template<typename DataType>
  void create_default_chebyshev1_coeffs(size_t order, DataType ripple, DataType Wn, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order), ripple, z, p, k);
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
  void create_bp_chebyshev1_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order/2), ripple, z, p, k);
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
  void create_bs_chebyshev1_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order/2), ripple, z, p, k);
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
  Chebyshev1LowPassCoefficients<DataType>::Chebyshev1LowPassCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequency(0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1LowPassCoefficients<DataType_>::set_ripple(DataType_ ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1LowPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType_>
  void Chebyshev1LowPassCoefficients<DataType_>::set_cut_frequency(DataType_ cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1LowPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void Chebyshev1LowPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev1LowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev1HighPassCoefficients<DataType>::Chebyshev1HighPassCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequency(0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1HighPassCoefficients<DataType_>::set_cut_frequency(DataType_ cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1HighPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType_>
  void Chebyshev1HighPassCoefficients<DataType_>::set_ripple(DataType_ ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1HighPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1HighPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev1HighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_default_chebyshev1_coeffs(in_order, ripple, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(int i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  Chebyshev1BandPassCoefficients<DataType>::Chebyshev1BandPassCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies)
  {
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_cut_frequencies(DataType_ f0, DataType_ f1)
  {
    this->cut_frequencies = std::make_pair(f0, f1);
    setup();
  }
  
  template <typename DataType_>
  std::pair<DataType_, DataType_> Chebyshev1BandPassCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_ripple(DataType_ ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1BandPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1BandPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev1BandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_bp_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev1BandStopCoefficients<DataType>::Chebyshev1BandStopCoefficients(int nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies)
  {
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_cut_frequencies(DataType_ f0, DataType_ f1)
  {
    this->cut_frequencies = std::make_pair(f0, f1);
    setup();
  }
  
  template <typename DataType_>
  std::pair<DataType_, DataType_> Chebyshev1BandStopCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_ripple(DataType_ ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  DataType_ Chebyshev1BandStopCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1BandStopCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  void Chebyshev1BandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_bs_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template class Chebyshev1LowPassCoefficients<float>;
  template class Chebyshev1LowPassCoefficients<double>;
  template class Chebyshev1HighPassCoefficients<float>;
  template class Chebyshev1HighPassCoefficients<double>;
  template class Chebyshev1BandPassCoefficients<float>;
  template class Chebyshev1BandPassCoefficients<double>;
  template class Chebyshev1BandStopCoefficients<float>;
  template class Chebyshev1BandStopCoefficients<double>;
  
  template class IIRFilter<Chebyshev1LowPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1LowPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1HighPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<float> >;
  template class IIRFilter<Chebyshev1BandPassCoefficients<double> >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<float> >;
  template class IIRFilter<Chebyshev1BandStopCoefficients<double> >;
  
}
