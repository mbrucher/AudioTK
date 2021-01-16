/**
 * \file RemezBasedFilter.cpp
 */

#include "RemezBasedFilter.h"
#include <ATK/Core/Utilities.h>
#include <ATK/EQ/FIRFilter.h>
#include <ATK/Utility/FFT.h>

#include <boost/math/constants/constants.hpp>

#include <Eigen/Dense>

#include <vector>

namespace
{
  template<class DataType>
  class RemezBuilder
  {
  public:
    using AlignedScalarVector = typename ATK::TypedBaseFilter<DataType>::AlignedScalarVector;
  private:
    const static gsl::index grid_size = 1024; // grid size, power of two better for FFT
    constexpr static DataType SN = 1e-8;

    gsl::index M;
    std::vector<DataType> grid;
    std::vector<std::pair<std::pair<DataType, DataType>, std::pair<DataType, DataType>> > target;
    
    /// Computed coefficients
    AlignedScalarVector coeffs;
    /// Selected indices
    std::vector<gsl::index> indices;
    /// Weight function on the grid
    std::vector<DataType> weights;
    /// Objective function on the grid
    std::vector<DataType> objective;
    /// Alternate signs
    std::vector<int> s;

    ATK::FFT<DataType> fft_processor;

  public:
    RemezBuilder(gsl::index order, const std::vector<std::pair<std::pair<DataType, DataType>, std::pair<DataType, DataType>> >& target)
    :M(order / 2), target(target)
    {
      grid.resize(grid_size);
      for(gsl::index i = 0; i < grid_size; ++i)
      {
        grid[i] = i * boost::math::constants::pi<DataType>() / grid_size;
      }
      fft_processor.set_size(2 * grid_size);
    }
    
    void init()
    {
      coeffs.assign(M * 2 + 1, 0);
      indices.assign(M + 2, -1);
      s.assign(M+2, 0);
      
      weights.assign(grid_size, 0);
      objective.assign(grid_size, 0);

      int current_template = 0;
      for(gsl::index i = 0; i < grid_size; ++i)
      {
        auto reduced_freq = grid[i] / boost::math::constants::pi<DataType>();
        if(reduced_freq > target[current_template].first.second && current_template + 1 < target.size())
        {
          ++current_template;
        }
        if (reduced_freq < target[current_template].first.first || reduced_freq > target[current_template].first.second)
        {
          weights[i] = 0;
          objective[i] = 0;
        }
        else
        {
          weights[i] = target[current_template].second.second;
          objective[i] = target[current_template].second.first;
        }
      }
      int flag = -1;
      for (gsl::index i = 0; i < M + 2; ++i)
      {
        s[i] = flag;
        flag = -flag;
      }
      indices = set_starting_conditions();
    }

    std::vector<gsl::index> set_starting_conditions() const
    {
      std::vector<gsl::index> indices;

      std::vector<gsl::index> valid_indices;
      for (gsl::index i = 0; i < grid_size; ++i)
      {
        if (weights[i] != 0)
        {
          valid_indices.push_back(i);
        }
      }

      for (gsl::index i = 0; i < M + 2; ++i)
      {
        indices.push_back(valid_indices[std::lround(valid_indices.size() / (M + 4.) * (i + 1))]);
      }

      return indices;
    }
    
    AlignedScalarVector build()
    {
      if(target.empty())
      {
        coeffs.clear();
        return coeffs;
      }
      init();
      while(true)
      {
        Eigen::Matrix<DataType, Eigen::Dynamic, Eigen::Dynamic> A(M + 2, M + 2);
        for (gsl::index i = 0; i < M + 2; ++i)
        {
          for (gsl::index j = 0; j < M + 1; ++j)
          {
            A(i, j) = std::cos(grid[indices[i]] * j);
          }
        }
        for (gsl::index i = 0; i < M + 2; ++i)
        {
          A(i, M + 1) = s[i] / weights[indices[i]];
        }

        Eigen::Matrix<DataType, Eigen::Dynamic, 1> b(M + 2, 1);
        for (gsl::index i = 0; i < M + 2; ++i)
        {
          b(i) = objective[indices[i]];
        }
        Eigen::Matrix<DataType, Eigen::Dynamic, 1> x = A.colPivHouseholderQr().solve(b);

        for (gsl::index i = 0; i < M; ++i)
        {
          coeffs[i] = coeffs[2 * M - i] = x[M - i] / 2;
        }
        coeffs[M] = x[0];
        auto delta = std::abs(x[M + 1]); // maximum cost

        auto newerr = compute_new_error();
        auto new_indices = locmax(newerr);

        filter_SN(delta, new_indices, newerr);
        filter_monotony(new_indices, newerr);

        DataType max = 0;
        for (auto indice : new_indices)
        {
          max = std::max(max, std::abs(newerr[indice]));
        }

        if ((max - delta) / delta < SN)
        {
          break;
        }

        indices = std::move(new_indices);
      }

      return coeffs;
    }
    
  private:
    /// Creates a spectral response for a given set of coeffs through an FFT
    std::vector<DataType> firamp() const
    {
      std::vector<std::complex<DataType>> output(grid_size * 2);
      fft_processor.process_forward(coeffs.data(), output.data(), coeffs.size());
      std::vector<DataType> amp(grid_size);
      for (gsl::index i = 0; i < grid_size; ++i)
      {
        amp[i] = (std::complex<DataType>(std::cos(M * grid[i]), std::sin(M * grid[i])) * output[i]).real() * grid_size * 2;
      }
      return amp;
    }

    std::vector<DataType> compute_new_error() const
    {
      auto fir_result = firamp();
      std::vector<DataType> newerr(grid_size);
      for (gsl::index i = 0; i < grid_size; ++i)
      {
        newerr[i] = (fir_result[i] - objective[i]) * weights[i];
      }

      return newerr;
    }

    // Finds min and max
    std::vector<gsl::index> locmax(const std::vector<DataType>& data) const
    {
      std::vector<gsl::index> v;

      std::vector<DataType> temp1;
      std::vector<DataType> temp2;
      temp1.push_back(data[0] - 1);
      for (gsl::index i = 0; i < data.size() - 1; ++i)
      {
        temp1.push_back(data[i]);
        temp2.push_back(data[i + 1]);
      }
      temp2.push_back(data.back() - 1);

      for (gsl::index i = 0; i < data.size(); ++i)
      {
        if ((data[i] > temp1[i]) && (data[i] > temp2[i]))
        {
          v.push_back(i);
        }
      }

      temp1.clear();
      temp2.clear();
      temp1.push_back(-data[0] - 1);
      for (gsl::index i = 0; i < data.size() - 1; ++i)
      {
        temp1.push_back(-data[i]);
        temp2.push_back(-data[i + 1]);
      }
      temp2.push_back(-data.back() - 1);

      for (gsl::index i = 0; i < data.size(); ++i)
      {
        if ((-data[i] > temp1[i]) && (-data[i] > temp2[i]))
        {
          v.push_back(i);
        }
      }

      std::sort(v.begin(), v.end());

      return v;
    }

    void filter_SN(DataType delta, std::vector<gsl::index>& indices, const std::vector<DataType>& err) const
    {
      std::vector<gsl::index> new_indices;

      for (auto indice : indices)
      {
        if (std::abs(err[indice]) > (delta - SN))
        {
          new_indices.push_back(indice);
        }
      }

      indices = std::move(new_indices);
    }

    std::vector<gsl::index> etap(const std::vector<DataType>& data) const
    {
      std::vector<gsl::index> v;
      auto xe = data[0];
      gsl::index xv = 0;
      for (gsl::index i = 1; i < data.size(); ++i)
      {
        if (std::signbit(data[i]) == std::signbit(xe))
        {
          if (std::abs(data[i]) > std::abs(xe))
          {
            xe = data[i];
            xv = i;
          }
        }
        else
        {
          v.push_back(xv);
          xe = data[i];
          xv = i;
        }
      }
      v.push_back(xv);
      return v;
    }

    void filter_monotony(std::vector<gsl::index>& indices, const std::vector<DataType>& err) const
    {
      std::vector<DataType> filtered_err;
      for (auto indice : indices)
      {
        filtered_err.push_back(err[indice]);
      }

      auto selected_indices = etap(filtered_err);
      std::vector<gsl::index> new_indices;
      for (gsl::index i = 0; i < M + 2; ++i)
      {
        new_indices.push_back(indices[selected_indices[i]]);
      }
      indices = std::move(new_indices);
    }
  };
}

namespace ATK
{
  template<class DataType>
  RemezBasedCoefficients<DataType>::RemezBasedCoefficients(gsl::index nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template<class DataType>
  RemezBasedCoefficients<DataType>::RemezBasedCoefficients(RemezBasedCoefficients&& other)
    :Parent(std::move(other)), target(std::move(other.target)), in_order(std::move(other.in_order)), coefficients_in(std::move(other.coefficients_in))
  {
  }

  template<class DataType>
  void RemezBasedCoefficients<DataType>::set_template(const std::vector<std::pair<std::pair<CoeffDataType, CoeffDataType>, std::pair<CoeffDataType, CoeffDataType> > >& target)
  {
    this->target = target;
    setup();
  }
  
  template<class DataType>
  const std::vector<std::pair<std::pair<typename RemezBasedCoefficients<DataType>::CoeffDataType, typename RemezBasedCoefficients<DataType>::CoeffDataType>, std::pair<typename RemezBasedCoefficients<DataType>::CoeffDataType, typename RemezBasedCoefficients<DataType>::CoeffDataType> > >& RemezBasedCoefficients<DataType>::get_template() const
  {
    return target;
  }
  
  template<class DataType>
  void RemezBasedCoefficients<DataType>::set_order(gsl::index order)
  {
    if(order % 2 == 1)
    {
      throw ATK::RuntimeError("Need an even filter order (considering order 0 has 1 coefficients)");
    }
    in_order = order;
    setup();
  }

  template<class DataType>
  void RemezBasedCoefficients<DataType>::setup()
  {
    Parent::setup();
    
    std::sort(target.begin(), target.end());
    for(gsl::index i = 0; i + 1 < target.size(); ++i)
    {
      if(target[i].first.second > target[i + 1].first.first)
      {
        target.clear();
        throw ATK::RuntimeError("Bad template");
      }
    }
    
    if (in_order > 0)
    {
      RemezBuilder<CoeffDataType> builder(in_order, target);
      coefficients_in = builder.build();
    }
  }
  
  template class ATK_EQ_EXPORT RemezBasedCoefficients<double>;
#if ATK_ENABLE_INSTANTIATION
  template class ATK_EQ_EXPORT RemezBasedCoefficients<std::complex<double> >;
#endif
}
