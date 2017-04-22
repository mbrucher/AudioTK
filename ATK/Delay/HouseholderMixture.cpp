/**
 * \file HouseholderMixture.cpp
 */

#include "FeedbackDelayNetworkFilter.hxx"
#include "HouseholderMixture.h"

#if ATK_EIGEN == 1

#include <complex>

#include <Eigen/Dense>

namespace ATK
{
  template<typename DataType_, unsigned int nb_channels>
  class HouseholderMixture<DataType_, nb_channels>::MixtureImpl
  {
  public:
    typedef Eigen::Matrix<DataType, nb_channels, 1> Vector;
    typedef Eigen::Matrix<DataType, nb_channels, nb_channels> Matrix;

    MixtureImpl()
      :transition(create())
    {
    }

    Vector mix(const Vector& x) const
    {
      return transition * x;
    }

  protected:
    const Matrix transition;
    
    static Matrix create()
    {
      return Matrix::Identity().array() - (DataType(2) / DataType(nb_channels));
    }
  };

  template class FeedbackDelayNetworkFilter<HouseholderMixture<float, 2>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<double, 2>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 2>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 2>>;

  template class FeedbackDelayNetworkFilter<HouseholderMixture<float, 4>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<double, 4>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 4>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 4>>;

  template class FeedbackDelayNetworkFilter<HouseholderMixture<float, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<double, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<float>, 8>>;
  template class FeedbackDelayNetworkFilter<HouseholderMixture<std::complex<double>, 8>>;
}

#endif
