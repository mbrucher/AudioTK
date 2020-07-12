/**
 * \file helpers.h
 */

#ifndef ATK_EQ_HELPERS_H
#define ATK_EQ_HELPERS_H

#include <cmath>
#include <vector>

#include <boost/math/tools/polynomial.hpp>

/// Namespace to build filters based on their zpk description
namespace EQUtilities
{
  // Factor paameters
  template<typename DataType>
  struct ZPK
  {
    std::vector<std::complex<DataType> > z;
    std::vector<std::complex<DataType> > p;
    DataType k;
  };
  
  /// Transform the Wn=1 low pass analog filter in a Wn=Wn low pass filter
  template<typename DataType>
  void zpk_lp2lp(DataType Wn, ZPK<DataType>& zpk)
  {
    auto z_size = zpk.z.size();
    auto p_size = zpk.p.size();

    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    for(gsl::index i = 0; i < z_size; ++i)
    {
      zpk.z[i] *= Wn;
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      zpk.p[i] *= Wn;
    }
    
    zpk.k *= static_cast<DataType>(std::pow(Wn, relative_degree));
  }

  /// Transform the Wn=1 low pass analog filter in a Wn=Wn, bw=bw band pass filter
  template<typename DataType>
  void zpk_lp2bp(DataType Wn, DataType bw, ZPK<DataType>& zpk)
  {
    auto z_size = zpk.z.size();
    auto p_size = zpk.p.size();
    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    for(gsl::index i = 0; i < z_size; ++i)
    {
      zpk.z[i] *= bw/2;
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      zpk.p[i] *= bw/2;
    }
    
    std::vector<std::complex<DataType> > zbp;
    std::vector<std::complex<DataType> > pbp;

    for(gsl::index i = 0; i < z_size; ++i)
    {
      zbp.push_back(zpk.z[i] + std::sqrt(zpk.z[i]*zpk.z[i] - Wn*Wn));
      zbp.push_back(zpk.z[i] - std::sqrt(zpk.z[i]*zpk.z[i] - Wn*Wn));
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      pbp.push_back(zpk.p[i] + std::sqrt(zpk.p[i]*zpk.p[i] - Wn*Wn));
      pbp.push_back(zpk.p[i] - std::sqrt(zpk.p[i]*zpk.p[i] - Wn*Wn));
    }

    zbp.resize(zbp.size() + relative_degree, 0);
    zpk.z.swap(zbp);
    zpk.p.swap(pbp);
    
    zpk.k *= static_cast<DataType>(std::pow(bw, relative_degree));
  }
  
  /// Transform the Wn=1 low pass analog filter in a Wn=Wn, bw=bw band stop filter
  template<typename DataType>
  void zpk_lp2bs(DataType Wn, DataType bw, ZPK<DataType>& zpk)
  {
    auto z_size = zpk.z.size();
    auto p_size = zpk.p.size();
    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    std::complex<DataType> f = 1;
    for(gsl::index i = 0; i < z_size; ++i)
    {
      f *= -zpk.z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      f /= -zpk.p[i];
    }
    zpk.k *= f.real();

    for(gsl::index i = 0; i < z_size; ++i)
    {
      zpk.z[i] = bw / 2 / zpk.z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      zpk.p[i] = bw / 2 / zpk.p[i];
    }
    
    std::vector<std::complex<DataType> > zbs;
    zbs.reserve(2 * z_size);
    std::vector<std::complex<DataType> > pbs;
    pbs.reserve(2 * p_size);
    
    for(gsl::index i = 0; i < z_size; ++i)
    {
      zbs.push_back(zpk.z[i] + std::sqrt(zpk.z[i]*zpk.z[i] - Wn*Wn));
      zbs.push_back(zpk.z[i] - std::sqrt(zpk.z[i]*zpk.z[i] - Wn*Wn));
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      pbs.push_back(zpk.p[i] + std::sqrt(zpk.p[i]*zpk.p[i] - Wn*Wn));
      pbs.push_back(zpk.p[i] - std::sqrt(zpk.p[i]*zpk.p[i] - Wn*Wn));
    }
    
    zbs.resize(zbs.size() + relative_degree, std::complex<DataType>(0, Wn));
    zbs.resize(zbs.size() + relative_degree, std::complex<DataType>(0, -Wn));
    zpk.z.swap(zbs);
    zpk.p.swap(pbs);
  }

  /// Apply a bilinear transform on z, p, k
  template<typename DataType>
  void zpk_bilinear(std::size_t fs, ZPK<DataType>& zpk)
  {
    auto z_size = zpk.z.size();
    auto p_size = zpk.p.size();

    DataType fs2 = 2 * static_cast<DataType>(fs);
  
    std::complex<DataType> f = 1;
    for(gsl::index i = 0; i < z_size; ++i)
    {
      f *= fs2 - zpk.z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      f /= fs2 - zpk.p[i];
    }
    zpk.k *= f.real();
    
    for(gsl::index i = 0; i < z_size; ++i)
    {
      zpk.z[i] = (fs2 + zpk.z[i]) / (fs2 - zpk.z[i]);
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      zpk.p[i] = (fs2 + zpk.p[i]) / (fs2 - zpk.p[i]);
    }
    
    zpk.z.resize(zpk.p.size(), -1);
  }

  /// Transforms the z, p, k coefficients in b, a form
  template<typename DataType>
  void zpk2ba(const ZPK<DataType>& zpk, boost::math::tools::polynomial<DataType>& b, boost::math::tools::polynomial<DataType>& a)
  {
    auto z_size = zpk.z.size();
    auto p_size = zpk.p.size();

    b = boost::math::tools::polynomial<DataType>({ zpk.k });

    for(gsl::index i = 0; i < z_size; ++i)
    {
      if(zpk.z[i].imag() == 0)
      {
        boost::math::tools::polynomial<DataType> poly1({ -zpk.z[i].real(), 1 });
        if (b.size() <= 1)
        {
          b = poly1 * zpk.k;
        }
        else
        {
          b *= poly1;
        }
      }
      else if(zpk.z[i].imag() < 0)
      {
        boost::math::tools::polynomial<DataType> poly2({ zpk.z[i].real() * zpk.z[i].real() + zpk.z[i].imag() * zpk.z[i].imag(), -2 * zpk.z[i].real(), 1 });
        if (b.size() <= 1)
        {
          b = poly2 * zpk.k;
        }
        else
        {
          b *= poly2;
        }
      }
    }
    
    a = boost::math::tools::polynomial<DataType>({1});
    for(gsl::index i = 0; i < p_size; ++i)
    {
      if(zpk.p[i].imag() == 0)
      {
        boost::math::tools::polynomial<DataType> poly1({ -zpk.p[i].real(), 1 });
        a *= poly1;
      }
      else if (zpk.p[i].imag() < 0)
      {
        boost::math::tools::polynomial<DataType> poly2({ zpk.p[i].real() * zpk.p[i].real() + zpk.p[i].imag() * zpk.p[i].imag(), -2 * zpk.p[i].real(), 1 });
        a *= poly2;
      }
    }
  }
  
  template<typename DataType, typename Container>
  void to_bilinear(const ZPK<DataType>& zpk, Container& coefficients_in, Container& coefficients_out, size_t order)
  {
    boost::math::tools::polynomial<DataType> b;
    boost::math::tools::polynomial<DataType> a;

    zpk2ba(zpk, b, a);
    
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
  void populate_lp_coeffs(DataType Wn, int fs, size_t order, ZPK<DataType>& zpk, Container& coefficients_in, Container& coefficients_out)
  {
    DataType warped = 2 * fs * std::tan(boost::math::constants::pi<DataType>() *  Wn / fs);
    zpk_lp2lp(warped, zpk);
    zpk_bilinear(fs, zpk);
    
    to_bilinear(zpk, coefficients_in, coefficients_out, order);
  }
  
  template<typename DataType, typename Container>
  void populate_bp_coeffs(DataType wc1, DataType wc2, int fs, size_t order, ZPK<DataType>& zpk, Container& coefficients_in, Container& coefficients_out)
  {
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bp(std::sqrt(wc1 * wc2), wc2 - wc1, zpk);
    zpk_bilinear(fs, zpk);
    
    to_bilinear(zpk, coefficients_in, coefficients_out, order);
  }
  
  template<typename DataType, typename Container>
  void populate_bs_coeffs(DataType wc1, DataType wc2, int fs, size_t order, ZPK<DataType>& zpk, Container& coefficients_in, Container& coefficients_out)
  {
    wc1 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc1 / fs);
    wc2 = 2 * fs * std::tan(boost::math::constants::pi<DataType>() * wc2 / fs);
    
    zpk_lp2bs(std::sqrt(wc1 * wc2), wc2 - wc1, zpk);
    zpk_bilinear(fs, zpk);
    
    to_bilinear(zpk, coefficients_in, coefficients_out, order);
  }
}

#endif
