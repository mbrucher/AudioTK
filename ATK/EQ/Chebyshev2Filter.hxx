/**
 * \file Chebyshev2Filter.hxx
 */

#include "Chebyshev2Filter.h"
#include <ATK/EQ/helpers.h>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/asinh.hpp>

namespace Chebyshev2Utilities
{
  template<typename DataType>
  void create_chebyshev2_analog_coefficients(int order, DataType ripple, EQUtilities::ZPK<DataType>& zpk)
  {
    zpk.z.clear(); // no zeros for this filter type
    zpk.p.clear();
    
    DataType de = static_cast<DataType>(1.0 / std::sqrt(std::pow(10, (0.1 * ripple)) - 1));
    DataType mu = static_cast<DataType>(boost::math::asinh(1.0 / de) / order);
    
    for(gsl::index i = -order+1; i < order; i += 2)
    {
      std::complex<DataType> p1 = -std::complex<DataType>(std::cos(i * boost::math::constants::pi<DataType>() / (2 * order)), std::sin(i * boost::math::constants::pi<DataType>() / (2 * order)));
      std::complex<DataType> p2 = std::complex<DataType>(std::sinh(mu) * p1.real(), std::cosh(mu) * p1.imag());
      
      zpk.p.push_back(std::complex<DataType>(1, 0) / p2);
      
      if(i == 0)
      {
        continue;
      }
      
      zpk.z.push_back(std::complex<DataType>(0, 1 / std::sin(i * boost::math::constants::pi<DataType>() / (2 * order))));
    }
    
    std::complex<DataType> f = 1;
    for(gsl::index i = 0; i < zpk.p.size(); ++i)
    {
      f *= - zpk.p[i];
    }
    for(gsl::index i = 0; i < zpk.z.size(); ++i)
    {
      f /= - zpk.z[i];
    }
    zpk.k = f.real();
  }
  
  template<typename DataType, typename Container>
  void create_default_chebyshev2_coeffs(size_t order, DataType ripple, DataType Wn, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order), ripple, zpk);
    EQUtilities::populate_lp_coeffs(Wn, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bp_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order/2), ripple, zpk);
    EQUtilities::populate_bp_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bs_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order/2), ripple, zpk);
    EQUtilities::populate_bs_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
}

namespace ATK
{
  template <typename DataType>
  Chebyshev2LowPassCoefficients<DataType>::Chebyshev2LowPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev2LowPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2LowPassCoefficients<DataType_>::CoeffDataType Chebyshev2LowPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType_>
  void Chebyshev2LowPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2LowPassCoefficients<DataType_>::CoeffDataType Chebyshev2LowPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev2LowPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void Chebyshev2LowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev2Utilities::create_default_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2HighPassCoefficients<DataType>::Chebyshev2HighPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev2HighPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2HighPassCoefficients<DataType_>::CoeffDataType Chebyshev2HighPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType_>
  void Chebyshev2HighPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2HighPassCoefficients<DataType_>::CoeffDataType Chebyshev2HighPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev2HighPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void Chebyshev2HighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev2Utilities::create_default_chebyshev2_coeffs(in_order, ripple, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(gsl::index i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  Chebyshev2BandPassCoefficients<DataType>::Chebyshev2BandPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev2BandPassCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev2BandPassCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename Chebyshev2BandPassCoefficients<DataType_>::CoeffDataType, typename Chebyshev2BandPassCoefficients<DataType_>::CoeffDataType> Chebyshev2BandPassCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev2BandPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2BandPassCoefficients<DataType_>::CoeffDataType Chebyshev2BandPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev2BandPassCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void Chebyshev2BandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev2Utilities::create_bp_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2BandStopCoefficients<DataType>::Chebyshev2BandStopCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev2BandStopCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev2BandStopCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename Chebyshev2BandStopCoefficients<DataType_>::CoeffDataType, typename Chebyshev2BandStopCoefficients<DataType_>::CoeffDataType> Chebyshev2BandStopCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev2BandStopCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev2BandStopCoefficients<DataType_>::CoeffDataType Chebyshev2BandStopCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev2BandStopCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void Chebyshev2BandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev2Utilities::create_bs_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
}
