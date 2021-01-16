/**
 * \file HouseholderMixture.hxx
 */

#include "HouseholderMixture.h"
#include <ATK/Delay/FeedbackDelayNetworkFilter.hxx>

#include <Eigen/Dense>

namespace ATK
{
  template<typename DataType_, unsigned int nb_channels>
  class HouseholderMixture<DataType_, nb_channels>::MixtureImpl
  {
  public:
    using Vector = Eigen::Matrix<DataType, nb_channels, 1>;
    using Matrix = Eigen::Matrix<DataType, nb_channels, nb_channels>;

    Vector mix(const Vector& x) const
    {
      return transition * x;
    }

  protected:
    const Matrix transition = create();
    
    static Matrix create()
    {
      return Matrix::Identity().array() - (DataType(2) / DataType(nb_channels));
    }
  };
}
