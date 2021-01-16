/**
 * \file ButterworthFilter.hxx
 */

#include "ButterworthFilter.h"
#include <ATK/EQ/helpers.h>

#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/polynomial.hpp>

namespace ButterworthUtilities
{
  template<typename DataType>
  void create_butterworth_analog_coefficients(int order, EQUtilities::ZPK<DataType>& zpk)
  {
    zpk.k = 1;
    zpk.z.clear(); // no zeros for this filter type
    zpk.p.clear();
    for(gsl::index i = -order+1; i < order; i += 2)
    {
      zpk.p.push_back(std::complex<DataType>(-std::cos(boost::math::constants::pi<DataType>() * i / (2 * order)), -std::sin(boost::math::constants::pi<DataType>() * i / (2 * order))));
    }
  }
  
  template<typename DataType, typename Container>
  void create_default_coeffs(size_t order, DataType Wn, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_butterworth_analog_coefficients(static_cast<int>(order), zpk);
    EQUtilities::populate_lp_coeffs(Wn, fs, order, zpk, coefficients_in, coefficients_out);
  }

  template<typename DataType, typename Container>
  void create_bp_coeffs(size_t order, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_butterworth_analog_coefficients(static_cast<int>(order/2), zpk);
    EQUtilities::populate_bp_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bs_coeffs(size_t order, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_butterworth_analog_coefficients(static_cast<int>(order/2), zpk);
    EQUtilities::populate_bs_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
}

namespace ATK
{
  template <typename DataType>
  ButterworthLowPassCoefficients<DataType>::ButterworthLowPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void ButterworthLowPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }

  template <typename DataType_>
  typename ButterworthLowPassCoefficients<DataType_>::CoeffDataType ButterworthLowPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int ButterworthLowPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void ButterworthLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    ButterworthUtilities::create_default_coeffs(in_order, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }

  template <typename DataType>
  ButterworthHighPassCoefficients<DataType>::ButterworthHighPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void ButterworthHighPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename ButterworthHighPassCoefficients<DataType_>::CoeffDataType ButterworthHighPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int ButterworthHighPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void ButterworthHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    ButterworthUtilities::create_default_coeffs(in_order, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(gsl::index i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }

  template <typename DataType>
  ButterworthBandPassCoefficients<DataType>::ButterworthBandPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType_>
  void ButterworthBandPassCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }

  template <typename DataType_>
  void ButterworthBandPassCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }

  template <typename DataType_>
  std::pair<typename ButterworthBandPassCoefficients<DataType_>::CoeffDataType, typename ButterworthBandPassCoefficients<DataType_>::CoeffDataType> ButterworthBandPassCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }

  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }

  template <typename DataType>
  unsigned int ButterworthBandPassCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    ButterworthUtilities::create_bp_coeffs(in_order, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }

  template <typename DataType>
  ButterworthBandStopCoefficients<DataType>::ButterworthBandStopCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void ButterworthBandStopCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void ButterworthBandStopCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename ButterworthBandStopCoefficients<DataType_>::CoeffDataType, typename ButterworthBandStopCoefficients<DataType_>::CoeffDataType> ButterworthBandStopCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void ButterworthBandStopCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int ButterworthBandStopCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void ButterworthBandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    ButterworthUtilities::create_bs_coeffs(in_order, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
}
