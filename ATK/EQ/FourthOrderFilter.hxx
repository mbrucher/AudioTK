/**
 * \file FourthOrderFilter.hxx
 */

#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/IIRFilter.h>

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
}
