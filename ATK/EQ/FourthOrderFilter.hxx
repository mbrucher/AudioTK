/**
 * \file FourthOrderFilter.hxx
 */

#include "FourthOrderFilter.h"
#include <ATK/EQ/IIRFilter.h>

#include <boost/math/constants/constants.hpp>

#include <cassert>
#include <cmath>

namespace ATK
{
  template <typename DataType_>
  FourthOrderBaseCoefficients<DataType_>::FourthOrderBaseCoefficients(gsl::index nb_channels)
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
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename FourthOrderBaseCoefficients<DataType_>::CoeffDataType FourthOrderBaseCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
}
