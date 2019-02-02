/**
 * \file HadamardMixture.hxx
 */

#include <ATK/Delay/FeedbackDelayNetworkFilter.hxx>
#include <ATK/Delay/HadamardMixture.h>

#include <Eigen/Dense>

#include <ATK/Core/TypeTraits.h>
#include <ATK/Utility/fmath.h>

namespace ATK
{
  template<typename DataType_, unsigned int order>
  class HadamardMixture<DataType_, order>::MixtureImpl
  {
  public:
    using Vector = Eigen::Matrix<DataType, nb_channels, 1>;
    using Matrix = Eigen::Matrix<DataType, nb_channels, nb_channels>;

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
      return (DataType_(1 / fmath::pow(2, order / 2.)) * recursive_create<order>()).template cast<DataType_>();
    }
    
    template<unsigned int recursive_order>
    static Eigen::Matrix<typename TypeTraits<DataType_>::Scalar, (1U<<recursive_order), (1U<<recursive_order)> recursive_create()
    {
      if constexpr(recursive_order == 0)
      {
        return Eigen::Matrix<typename TypeTraits<DataType_>::Scalar, 1U, 1U>::Constant(1);
      }
      else
      {
        constexpr auto big_size = (1U << recursive_order);
        constexpr auto small_size = (1U << (recursive_order - 1));
        Eigen::Matrix<typename TypeTraits<DataType_>::Scalar, big_size, big_size> cur_transition;
        
        auto M_1 = recursive_create<recursive_order - 1>();
        cur_transition.block(0, 0, small_size, small_size) = M_1;
        cur_transition.block(0, small_size, small_size, small_size) = M_1;
        cur_transition.block(small_size, 0, small_size, small_size) = -M_1;
        cur_transition.block(small_size, small_size, small_size, small_size) = M_1;
        return cur_transition;
      }
    }
  };
}
