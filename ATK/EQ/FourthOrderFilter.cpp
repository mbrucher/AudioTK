/**
 * \file FourthOrderFilter.cpp
 */

#include "FourthOrderFilter.h"
#include "IIRFilter.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template <typename DataType_>
  FourthOrderBaseCoefficients<DataType_>::FourthOrderBaseCoefficients(std::size_t nb_channels)
    :Parent(nb_channels, nb_channels)
  {
  }

  template <typename DataType_>
  void FourthOrderBaseCoefficients<DataType_>::setup()
  {
    Parent::setup();

    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
  }

  template <typename DataType_>
  void FourthOrderBaseCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename FourthOrderBaseCoefficients<DataType_>::CoeffDataType FourthOrderBaseCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }

  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<float>::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<float>::setup();
  template ATK_EQ_EXPORT float FourthOrderBaseCoefficients<float>::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<float>::set_cut_frequency(float);
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<double>::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<double>::setup();
  template ATK_EQ_EXPORT double FourthOrderBaseCoefficients<double>::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<double>::set_cut_frequency(double);

  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<std::complex<float> >::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<float> >::setup();
  template ATK_EQ_EXPORT float FourthOrderBaseCoefficients<std::complex<float> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<float> >::set_cut_frequency(float);
  template ATK_EQ_EXPORT FourthOrderBaseCoefficients<std::complex<double> >::FourthOrderBaseCoefficients(std::size_t);
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<double> >::setup();
  template ATK_EQ_EXPORT double FourthOrderBaseCoefficients<std::complex<double> >::get_cut_frequency() const;
  template ATK_EQ_EXPORT void FourthOrderBaseCoefficients<std::complex<double> >::set_cut_frequency(double);
}
