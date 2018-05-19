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
  /// Transform the Wn=1 low pass analog filter in a Wn=Wn low pass filter
  template<typename DataType>
  void zpk_lp2lp(DataType Wn, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    auto z_size = z.size();
    auto p_size = p.size();

    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    for(gsl::index i = 0; i < z_size; ++i)
    {
      z[i] *= Wn;
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      p[i] *= Wn;
    }
    
    k *= static_cast<DataType>(std::pow(Wn, relative_degree));
  }

  /// Transform the Wn=1 low pass analog filter in a Wn=Wn, bw=bw band pass filter
  template<typename DataType>
  void zpk_lp2bp(DataType Wn, DataType bw, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    auto z_size = z.size();
    auto p_size = p.size();
    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    for(gsl::index i = 0; i < z_size; ++i)
    {
      z[i] *= bw/2;
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      p[i] *= bw/2;
    }
    
    std::vector<std::complex<DataType> > zbp;
    std::vector<std::complex<DataType> > pbp;

    for(gsl::index i = 0; i < z_size; ++i)
    {
      zbp.push_back(z[i] + std::sqrt(z[i]*z[i] - Wn*Wn));
      zbp.push_back(z[i] - std::sqrt(z[i]*z[i] - Wn*Wn));
    }
    for(gsl::index i = 0; i < p_size; ++i)
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
    auto z_size = z.size();
    auto p_size = p.size();
    int relative_degree = static_cast<int>(p_size) - static_cast<int>(z_size);

    std::complex<DataType> f = 1;
    for(gsl::index i = 0; i < z_size; ++i)
    {
      f *= - z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      f /= - p[i];
    }
    k *= f.real();

    for(gsl::index i = 0; i < z_size; ++i)
    {
      z[i] = bw / 2 / z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      p[i] = bw / 2 / p[i];
    }
    
    std::vector<std::complex<DataType> > zbs;
    std::vector<std::complex<DataType> > pbs;
    
    for(gsl::index i = 0; i < z_size; ++i)
    {
      zbs.push_back(z[i] + std::sqrt(z[i]*z[i] - Wn*Wn));
      zbs.push_back(z[i] - std::sqrt(z[i]*z[i] - Wn*Wn));
    }
    for(gsl::index i = 0; i < p_size; ++i)
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
  void zpk_bilinear(std::size_t fs, std::vector<std::complex<DataType> >& z, std::vector<std::complex<DataType> >& p, DataType& k)
  {
    auto z_size = z.size();
    auto p_size = p.size();

    DataType fs2 = 2 * static_cast<DataType>(fs);
  
    std::complex<DataType> f = 1;
    for(gsl::index i = 0; i < z_size; ++i)
    {
      f *= fs2 - z[i];
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      f /= fs2 - p[i];
    }
    k *= f.real();
    
    for(gsl::index i = 0; i < z_size; ++i)
    {
      z[i] = (fs2 + z[i]) / (fs2 - z[i]);
    }
    for(gsl::index i = 0; i < p_size; ++i)
    {
      p[i] = (fs2 + p[i]) / (fs2 - p[i]);
    }
    
    z.resize(p.size(), -1);
  }

  /// Transforms the z, p, k coefficients in b, a form
  template<typename DataType>
  void zpk2ba(std::size_t fs, const std::vector<std::complex<DataType> >& z, const std::vector<std::complex<DataType> >& p, DataType k, boost::math::tools::polynomial<DataType>& b, boost::math::tools::polynomial<DataType>& a)
  {
    auto z_size = z.size();
    auto p_size = p.size();

    b = boost::math::tools::polynomial<DataType>({ k });

    for(gsl::index i = 0; i < z_size; ++i)
    {
      if(z[i].imag() == 0)
      {
        boost::math::tools::polynomial<DataType> poly1({ -z[i].real(), 1 });
        if (b.size() <= 1)
        {
          b = poly1 * k;
        }
        else
        {
          b *= poly1;
        }
      }
      else if(z[i].imag() < 0)
      {
        boost::math::tools::polynomial<DataType> poly2({ z[i].real() * z[i].real() + z[i].imag() * z[i].imag(), -2 * z[i].real(), 1 });
        if (b.size() <= 1)
        {
          b = poly2 * k;
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
      if(p[i].imag() == 0)
      {
        boost::math::tools::polynomial<DataType> poly1({ -p[i].real(), 1 });
        a *= poly1;
      }
      else if (p[i].imag() < 0)
      {
        boost::math::tools::polynomial<DataType> poly2({ p[i].real() * p[i].real() + p[i].imag() * p[i].imag(), -2 * p[i].real(), 1 });
        a *= poly2;
      }
    }
  }
}

#endif
