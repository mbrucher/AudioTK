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
#include <type_traits>

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
      return recursive_create<order>();
    }
    
    template<unsigned int recursive_order>
    static typename std::enable_if<recursive_order == 0, Eigen::Matrix<DataType_, 1, 1>>::type recursive_create()
    {
      return Eigen::Matrix<DataType_, 1, 1>::Constant(1);
    }
    
    template<unsigned int recursive_order>
    static typename std::enable_if<recursive_order != 0, Eigen::Matrix<DataType_, 1<<recursive_order, 1<<recursive_order>>::type recursive_create()
    {
      constexpr auto big_size = 1 << recursive_order;
      constexpr auto small_size = 1 << (recursive_order - 1);
      Eigen::Matrix<DataType_, big_size, big_size> cur_transition;
      
      auto M_1 = recursive_create<recursive_order - 1>();
      cur_transition.block(0, 0, small_size, small_size) = M_1;
      cur_transition.block(0, small_size, small_size, small_size) = M_1;
      cur_transition.block(small_size, 0, small_size, small_size) = -M_1;
      cur_transition.block(small_size, small_size, small_size, small_size) = M_1;
      return cur_transition;
    }
  };

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 1>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 1>>;

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 2>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 2>>;

  template class FeedbackDelayNetworkFilter<HadamardMixture<float, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<double, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<float>, 3>>;
  template class FeedbackDelayNetworkFilter<HadamardMixture<std::complex<double>, 3>>;
}

#endif
