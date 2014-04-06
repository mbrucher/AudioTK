/**
 * \file ButterworthFilter.cpp
 */

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
      coefficients_out[i] = -a[i];
    }
  }
  
  template<typename DataType>
  void create_bp_coeffs(int order, DataType bp, DataType Wn, std::vector<DataType>& coefficients_in, std::vector<DataType>& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_butterworth_analog_coefficients(order/2, z, p, k);
    zpk_lp2bp(Wn, bp, z, p, k);
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
      coefficients_out[i] = -a[i];
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
    
    create_default_coeffs(in_order, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
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
    
    create_default_coeffs(in_order, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(int i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  ButterworthBandPassCoefficients<DataType>::ButterworthBandPassCoefficients()
  :Parent(1, 1), in_order(1), out_order(1)
  {
  }
  
  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::set_cut_frequencies(std::pair<DataType, DataType> cut_frequencies)
  {
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::set_cut_frequencies(DataType f0, DataType f1)
  {
    this->cut_frequencies = std::make_pair(f0, f1);
    setup();
  }

  template <typename DataType>
  std::pair<typename ButterworthBandPassCoefficients<DataType>::DataType, typename ButterworthBandPassCoefficients<DataType>::DataType> ButterworthBandPassCoefficients<DataType>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::set_order(int order)
  {
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  void ButterworthBandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    create_bp_coeffs(in_order, 2 * (cut_frequencies.second - cut_frequencies.first) / input_sampling_rate, 2 * std::sqrt(cut_frequencies.second * cut_frequencies.first) / input_sampling_rate, coefficients_in, coefficients_out);
  }

  template class ButterworthLowPassCoefficients<float>;
  template class ButterworthLowPassCoefficients<double>;
  template class ButterworthHighPassCoefficients<float>;
  template class ButterworthHighPassCoefficients<double>;
  template class ButterworthBandPassCoefficients<float>;
  template class ButterworthBandPassCoefficients<double>;
  
  template class IIRFilter<ButterworthLowPassCoefficients<float> >;
  template class IIRFilter<ButterworthLowPassCoefficients<double> >;
  template class IIRFilter<ButterworthHighPassCoefficients<float> >;
  template class IIRFilter<ButterworthHighPassCoefficients<double> >;
  template class IIRFilter<ButterworthBandPassCoefficients<float> >;
  template class IIRFilter<ButterworthBandPassCoefficients<double> >;

}
