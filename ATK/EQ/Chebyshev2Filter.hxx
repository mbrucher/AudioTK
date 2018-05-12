/**
 * \file Chebyshev2Filter.hxx
 */

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/asinh.hpp>

#include <ATK/EQ/Chebyshev2Filter.h>
#include <ATK/EQ/helpers.h>

namespace
{
  template<typename DataType>
  void create_chebyshev2_analog_coefficients(int order, DataType ripple, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    z.clear(); // no zeros for this filter type
    p.clear();
    
    DataType de = static_cast<DataType>(1.0 / std::sqrt(std::pow(10, (0.1 * ripple)) - 1));
    DataType mu = static_cast<DataType>(boost::math::asinh(1.0 / de) / order);
    
    for(gsl::index i = -order+1; i < order; i += 2)
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
    for(gsl::index i = 0; i < p.size(); ++i)
    {
      f *= - p[i];
    }
    for(gsl::index i = 0; i < z.size(); ++i)
    {
      f /= - z[i];
    }
    k = f.real();
  }
  
  template<typename DataType, typename Container>
  void create_default_chebyshev2_coeffs(size_t order, DataType ripple, DataType Wn, Container& coefficients_in, Container& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order), ripple, z, p, k);
    DataType warped = 2 * fs * std::tan(boost::math::constants::pi<DataType>() *  Wn / fs);
    zpk_lp2lp(warped, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b({ 1 });
    boost::math::tools::polynomial<DataType> a({ 1 });

    zpk2ba(fs, z, p, k, b, a);
    
    auto in_size = std::min(order + 1, b.size());
    for (size_t i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(order, a.size() - 1);
    for (size_t i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
  
  template<typename DataType, typename Container>
  void create_bp_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order/2), ripple, z, p, k);
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bp(std::sqrt(wc1 * wc2), wc2 - wc1, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b({ 1 });
    boost::math::tools::polynomial<DataType> a({ 1 });

    zpk2ba(fs, z, p, k, b, a);
    
    auto in_size = std::min(order + 1, b.size());
    for (size_t i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(order, a.size() - 1);
    for (size_t i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
  
  template<typename DataType, typename Container>
  void create_bs_chebyshev2_coeffs(size_t order, DataType ripple, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
    
    int fs = 2;
    create_chebyshev2_analog_coefficients(static_cast<int>(order/2), ripple, z, p, k);
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bs(std::sqrt(wc1 * wc2), wc2 - wc1, z, p, k);
    zpk_bilinear(fs, z, p, k);
    
    boost::math::tools::polynomial<DataType> b({ 1 });
    boost::math::tools::polynomial<DataType> a({ 1 });

    zpk2ba(fs, z, p, k, b, a);
    
    auto in_size = std::min(order + 1, b.size());
    for (size_t i = 0; i < in_size; ++i)
    {
      coefficients_in[i] = b[i];
    }
    auto out_size = std::min(order, a.size() - 1);
    for (size_t i = 0; i < out_size; ++i)
    {
      coefficients_out[i] = -a[i];
    }
  }
}

namespace ATK
{
  template <typename DataType>
  Chebyshev2LowPassCoefficients<DataType>::Chebyshev2LowPassCoefficients(std::size_t nb_channels)
  :Parent(1, 1), cut_frequency(0), ripple(0), in_order(1), out_order(1)
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
    
    create_default_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2HighPassCoefficients<DataType>::Chebyshev2HighPassCoefficients(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequency(0), ripple(0), in_order(1), out_order(1)
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
    
    create_default_chebyshev2_coeffs(in_order, ripple, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(gsl::index i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  Chebyshev2BandPassCoefficients<DataType>::Chebyshev2BandPassCoefficients(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
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
    
    create_bp_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  Chebyshev2BandStopCoefficients<DataType>::Chebyshev2BandStopCoefficients(std::size_t nb_channels)
  :Parent(nb_channels, nb_channels), cut_frequencies(0, 0), ripple(0), in_order(1), out_order(1)
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
    
    create_bs_chebyshev2_coeffs(in_order, ripple, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
}
