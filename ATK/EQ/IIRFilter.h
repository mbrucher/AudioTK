/**
 * \file IIRFilter.h
 */

#ifndef ATK_EQ_IIRFILTER_H
#define ATK_EQ_IIRFILTER_H

#include <cmath>
#include <vector>

#include <boost/math/tools/polynomial.hpp>

#include "config.h"

/// Namespace to build filters based on their zpk description
namespace
{
  /// Transform the Wn=1 low pass analog filter in a Wn=Wn low pass filter
  template<typename DataType>
  void zpk_lp2lp(DataType Wn, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    size_t relative_degree = p.size() - z.size();
    
    for(size_t i = 0; i < z.size(); ++i)
    {
      z[i] *= Wn;
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      p[i] *= Wn;
    }
    
    k *= static_cast<DataType>(std::pow(Wn, relative_degree));
  }

  /// Transform the Wn=1 low pass analog filter in a Wn=Wn, bw=bw band pass filter
  template<typename DataType>
  void zpk_lp2bp(DataType Wn, DataType bw, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    size_t relative_degree = p.size() - z.size();
    
    for(size_t i = 0; i < z.size(); ++i)
    {
      z[i] *= bw/2;
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      p[i] *= bw/2;
    }
    
    std::vector<std::complex<DataType> > zbp;
    std::vector<std::complex<DataType> > pbp;

    for(size_t i = 0; i < z.size(); ++i)
    {
      zbp.push_back(z[i] + std::sqrt(z[i]*z[i] - Wn*Wn));
      zbp.push_back(z[i] - std::sqrt(z[i]*z[i] - Wn*Wn));
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      pbp.push_back(p[i] + std::sqrt(p[i]*p[i] - Wn*Wn));
      pbp.push_back(p[i] - std::sqrt(p[i]*p[i] - Wn*Wn));
    }

    zbp.resize(zbp.size() + relative_degree, 0);
    z.swap(zbp);
    p.swap(pbp);
    
    k *= static_cast<DataType>(std::pow(bw, relative_degree));
  }
  
  /// Transform the Wn=1 low pass analog filter in a Wn=Wn, bw=bw band stop filter
  template<typename DataType>
  void zpk_lp2bs(DataType Wn, DataType bw, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    int relative_degree = static_cast<int>(p.size()) - static_cast<int>(z.size());
  
    std::complex<DataType> f = 1;
    for(size_t i = 0; i < z.size(); ++i)
    {
      f *= - z[i];
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      f /= - p[i];
    }
    k *= f.real();

    for(size_t i = 0; i < z.size(); ++i)
    {
      z[i] = bw / 2 / z[i];
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      p[i] = bw / 2 / p[i];
    }
    
    std::vector<std::complex<DataType> > zbs;
    std::vector<std::complex<DataType> > pbs;
    
    for(size_t i = 0; i < z.size(); ++i)
    {
      zbs.push_back(z[i] + std::sqrt(z[i]*z[i] - Wn*Wn));
      zbs.push_back(z[i] - std::sqrt(z[i]*z[i] - Wn*Wn));
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      pbs.push_back(p[i] + std::sqrt(p[i]*p[i] - Wn*Wn));
      pbs.push_back(p[i] - std::sqrt(p[i]*p[i] - Wn*Wn));
    }
    
    zbs.resize(zbs.size() + relative_degree, std::complex<DataType>(0, Wn));
    zbs.resize(zbs.size() + relative_degree, std::complex<DataType>(0, -Wn));
    z.swap(zbs);
    p.swap(pbs);
  }

  /// Apply a bilinear transform on z, p, k
  template<typename DataType>
  void zpk_bilinear(int fs, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    DataType fs2 = 2 * static_cast<DataType>(fs);
  
    std::complex<DataType> f = 1;
    for(size_t i = 0; i < z.size(); ++i)
    {
      f *= fs2 - z[i];
    }
    for(size_t i = 0; i < p.size(); ++i)
    {
      f /= fs2 - p[i];
    }
    k *= f.real();
    
    for(size_t i = 0; i < z.size(); ++i)
    {
      z[i] = (fs2 + z[i]) / (fs2 - z[i]);
    }
    for(size_t i = 0; i < p.size(); ++i)
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
    for(size_t i = 0; i < p.size(); ++i)
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
}

namespace ATK
{
  /**
   * IIR filter template class
   */
  template<class Coefficients >
  class ATK_EQ_EXPORT IIRFilter: public Coefficients
  {
  public:
    typedef Coefficients Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    
    using Parent::in_order;
    using Parent::out_order;
    using Parent::input_delay;
    using Parent::output_delay;
    using Parent::setup;
    
  public:
    IIRFilter(int nb_channels = 1)
      :Parent(nb_channels)
    {
    }

    void setup()
    {
      Parent::setup();
      input_delay = in_order;
      output_delay = out_order;
    }
    
    virtual void process_impl(std::int64_t size)
    {
      assert(input_sampling_rate == output_sampling_rate);
      assert(nb_input_ports == nb_output_ports);
      
      DataType tempout = 0;
      
      for(int channel = 0; channel < nb_input_ports; ++channel)
      {
        const DataType* ATK_RESTRICT input = converted_inputs[channel];
        DataType* ATK_RESTRICT output = outputs[channel];
        for(std::int64_t i = 0; i < size; ++i)
        {
          tempout = coefficients_in[in_order] * input[i];

          for(int j = 0; j < in_order; ++j)
          {
            tempout += coefficients_in[j] * input[i - in_order + j];
          }
          for(int j = 0; j < out_order; ++j)
          {
            tempout += coefficients_out[j] * output[i - out_order + j];
          }
          output[i] = tempout;
        }
      }
    }
    
    const std::vector<DataType>& get_coefficients_in() const
    {
      return coefficients_in;
    }
    
    const std::vector<DataType>& get_coefficients_out() const
    {
      return coefficients_out;
    }
  };

}

#endif
