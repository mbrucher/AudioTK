/**
 * \file BesselFilter.h
 */

#ifndef ATK_EQ_SIMD_BESSELFILTER_H
#define ATK_EQ_SIMD_BESSELFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/EQ/config.h>

namespace ATK
{
  template<typename DataType, std::size_t VL>
  ATK_EQ_EXPORT std::unique_ptr<BaseFilter> createLowPassBesselFilter(std::size_t nb_channels);
}

#endif
