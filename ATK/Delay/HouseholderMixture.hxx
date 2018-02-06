/**
 * \file HouseholderMixture.hxx
 */

#include <ATK/Delay/FeedbackDelayNetworkFilter.hxx>
#include <ATK/Delay/HouseholderMixture.h>

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
}
