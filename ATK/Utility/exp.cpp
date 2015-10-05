/**
 * \file exp.cpp
 */

#include <ATK/Utility/exp.h>

#include <cmath>

namespace ATK
{
  template<class DataType>
  Exp<DataType>::Exp(DataType max, int steps)
    :scale(max / steps), invscale(steps / max)
  {
    LUT.reserve(steps);
    for(int i = 0; i < steps; ++i)
    {
      LUT.push_back(std::exp(i * scale));
    }
  }
  
  template<class DataType>
  DataType Exp<DataType>::operator()(DataType value) const
  {
    if(value < 0)
    {
      return 1/(*this)(-value);
    }
    size_t step = static_cast<size_t>(value * invscale);
    if(step >= LUT.size())
    {
      step = LUT.size() - 1;
    }
    DataType delta = value - step * scale;
    return LUT[step] * (1 + delta + delta*delta/2);
  }

  template class Exp<float>;
  template class Exp<double>;
}
