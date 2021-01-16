/**
 * \file Chebyshev1Filter.hxx
 */

#include "Chebyshev1Filter.h"
#include <ATK/EQ/helpers.h>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/asinh.hpp>

namespace Chebyshev1Utilities
{
  template<typename DataType>
  void create_chebyshev1_analog_coefficients(int order, DataType ripple, EQUtilities::ZPK<DataType>& zpk)
  {
    zpk.z.clear(); // no zeros for this filter type
    zpk.p.clear();
    if(ripple == 0)
    {
      return;
    }
    if(order == 0)
    {
      zpk.k = static_cast<DataType>(std::pow(10, (-ripple / 20)));
      return;
    }
    
    DataType eps = static_cast<DataType>(std::sqrt(std::pow(10, (0.1 * ripple)) - 1.0));
    DataType mu = static_cast<DataType>(1.0 / order * boost::math::asinh(1 / eps));
    
    for(gsl::index i = -order+1; i < order; i += 2)
    {
      DataType theta = boost::math::constants::pi<DataType>() * i / (2*order);
      zpk.p.push_back(-std::sinh(std::complex<DataType>(mu, theta)));
    }

    std::complex<DataType> f = 1;
    
    for(gsl::index i = 0; i < zpk.p.size(); ++i)
    {
      f *= -zpk.p[i];
    }
    zpk.k = f.real();
    if(order % 2 == 0)
    {
      zpk.k = zpk.k / std::sqrt(1 + eps * eps);
    }
  }
  
  template<typename DataType, typename Container>
  void create_default_chebyshev1_coeffs(size_t order, DataType ripple, DataType Wn, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order), ripple, zpk);
    EQUtilities::populate_lp_coeffs(Wn, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bp_chebyshev1_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order/2), ripple, zpk);
    EQUtilities::populate_bp_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bs_chebyshev1_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_chebyshev1_analog_coefficients(static_cast<int>(order/2), ripple, zpk);
    EQUtilities::populate_bs_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
}

namespace ATK
{
  template <typename DataType>
  Chebyshev1LowPassCoefficients<DataType>::Chebyshev1LowPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1LowPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1LowPassCoefficients<DataType_>::CoeffDataType Chebyshev1LowPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }
  
  template <typename DataType_>
  void Chebyshev1LowPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1LowPassCoefficients<DataType_>::CoeffDataType Chebyshev1LowPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void Chebyshev1LowPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev1LowPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void Chebyshev1LowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev1Utilities::create_default_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev1HighPassCoefficients<DataType>::Chebyshev1HighPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1HighPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1HighPassCoefficients<DataType_>::CoeffDataType Chebyshev1HighPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType_>
  void Chebyshev1HighPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1HighPassCoefficients<DataType_>::CoeffDataType Chebyshev1HighPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1HighPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev1HighPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void Chebyshev1HighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev1Utilities::create_default_chebyshev1_coeffs(in_order, ripple, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(gsl::index i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  Chebyshev1BandPassCoefficients<DataType>::Chebyshev1BandPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename Chebyshev1BandPassCoefficients<DataType_>::CoeffDataType, typename Chebyshev1BandPassCoefficients<DataType_>::CoeffDataType> Chebyshev1BandPassCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev1BandPassCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1BandPassCoefficients<DataType_>::CoeffDataType Chebyshev1BandPassCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1BandPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev1BandPassCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void Chebyshev1BandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev1Utilities::create_bp_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev1BandStopCoefficients<DataType>::Chebyshev1BandStopCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename Chebyshev1BandStopCoefficients<DataType_>::CoeffDataType, typename Chebyshev1BandStopCoefficients<DataType_>::CoeffDataType> Chebyshev1BandStopCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType_>
  void Chebyshev1BandStopCoefficients<DataType_>::set_ripple(CoeffDataType ripple)
  {
    this->ripple = ripple;
    setup();
  }
  
  template <typename DataType_>
  typename Chebyshev1BandStopCoefficients<DataType_>::CoeffDataType Chebyshev1BandStopCoefficients<DataType_>::get_ripple() const
  {
    return ripple;
  }

  template <typename DataType>
  void Chebyshev1BandStopCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int Chebyshev1BandStopCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void Chebyshev1BandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    Chebyshev1Utilities::create_bs_chebyshev1_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
}
