/**
 * \file HadamardMixture.cpp
 */

#include "FeedbackDelayNetworkFilter.hxx"
#include "HadamardMixture.h"

#if ATK_EIGEN == 1

#include <cmath>
#include <cstring>
#include <complex>
#include <stdexcept>

#include <ATK/Core/TypeTraits.h>

#include <Eigen/Dense>

namespace ATK
{
  template<typename DataType_, unsigned int order>
  class HadamardMixture<DataType_, order>::MixtureImpl
  {
  public:
    typedef Eigen::Matrix<DataType, nb_channels, 1> Vector;
    typedef Eigen::Matrix<DataType, nb_channels, nb_channels> Matrix;

    Matrix create() const
    {
      Matrix transition;
      transition << 1, 1, 1, 1,
        1, -1, 1, -1,
        -1, -1, 1, 1,
        -1, 1, 1, -1;
      return transition;
    }

  };

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>;
}

#endif