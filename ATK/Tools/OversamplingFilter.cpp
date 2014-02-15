/**
 * \file OversamplingFilter.cpp
 */

#include "OversamplingFilter.h"

namespace ATK
{
  template<class DataType_>
  Oversampling6points5order_2<DataType_>::Oversampling6points5order_2()
  {
    coeffs[0][0] = 0.40513396007145713;
    coeffs[0][1] = 0.09251794438424393;
    coeffs[0][2] = 0.00234806603570670;
    coeffs[1][0] = 0.28342806338906690;
    coeffs[1][1] = 0.21703277024054901;
    coeffs[1][2] = 0.01309294748731515;
    coeffs[2][0] = -0.191337682540351941;
    coeffs[2][1] = 0.16187844487943592;
    coeffs[2][2] = 0.02946017143111912;
    coeffs[3][0] = -0.16471626390554542;
    coeffs[3][1] = -0.00154547203542499;
    coeffs[3][2] = 0.03399271444851909;
    coeffs[4][0] = 0.03845798729588149;
    coeffs[4][1] = -0.05712936104242644;
    coeffs[4][2] = 0.01866750929921070;
    coeffs[5][0] = 0.04317950185225609;
    coeffs[5][1] = -0.01802814255926417;
    coeffs[5][2] = 0.00152170021558204;
  }

  template<class DataType_>
  Oversampling6points5order_4<DataType_>::Oversampling6points5order_4()
  {
    coeffs[0][0] = 0.41496902959240894;
    coeffs[0][1] = 0.08343081932889224;
    coeffs[0][2] = 0.00160015038681571;
    coeffs[1][0] = 0.31625515004859783;
    coeffs[1][1] = 0.21197848565176958;
    coeffs[1][2] = 0.02337283412161328;
    coeffs[2][0] = -0.203271896548875371;
    coeffs[2][1] = 0.17989908432249280;
    coeffs[2][2] = 0.02337283412161328;
    coeffs[3][0] = -0.20209241069835732;
    coeffs[3][1] = 0.01760734419526000;
    coeffs[3][2] = 0.02985927012435252;
    coeffs[4][0] = 0.04100948858761910;
    coeffs[4][1] = -0.06147760875085254;
    coeffs[4][2] = 0.02046802954581191;
    coeffs[5][0] = 0.06607747864416924;
    coeffs[5][1] = -0.03255079211953620;
    coeffs[5][2] = 0.00628989632244913;
  }

  template<class DataType_>
  Oversampling6points5order_8<DataType_>::Oversampling6points5order_8()
  {
    coeffs[0][0] = 0.41660797292569773;
    coeffs[0][1] = 0.08188468587188069;
    coeffs[0][2] = 0.00150734119050266;
    coeffs[1][0] = 0.32232780822726981;
    coeffs[1][1] = 0.21076321997422021;
    coeffs[1][2] = 0.00907649978070957;
    coeffs[2][0] = -0.205219993961471501;
    coeffs[2][1] = 0.18282942057327367;
    coeffs[2][2] = 0.02239057377093268;
    coeffs[3][0] = -0.21022298520246224;
    coeffs[3][1] = 0.02176417471349534;
    coeffs[3][2] = 0.02898626924395209;
    coeffs[4][0] = 0.04149963966704384;
    coeffs[4][1] = -0.06224707096203808;
    coeffs[4][2] = 0.02074742969707599;
    coeffs[5][0] = 0.07517133281176167;
    coeffs[5][1] = -0.03751837438141215;
    coeffs[5][2] = 0.00747588873055296;
  }

  template<class DataType_>
  Oversampling6points5order_16<DataType_>::Oversampling6points5order_16()
  {
    coeffs[0][0] = 0.41809989254549901;
    coeffs[0][1] = 0.08049339946273310;
    coeffs[0][2] = 0.00140670799165932;
    coeffs[1][0] = 0.32767596257424964;
    coeffs[1][1] = 0.20978189376640677;
    coeffs[1][2] = 0.00859567104974701;
    coeffs[2][0] = -0.2069944618112960001;
    coeffs[2][1] = 0.18541689550861262;
    coeffs[2][2] = 0.02152772260740132;
    coeffs[3][0] = -0.21686095413034051;
    coeffs[3][1] = 0.02509557922091643;
    coeffs[3][2] = 0.02831484751363800;
    coeffs[4][0] = 0.04163046817137675;
    coeffs[4][1] = -0.06244556931623735;
    coeffs[4][2] = 0.02081510113314315;
    coeffs[5][0] = 0.07990500783668089;
    coeffs[5][1] = -0.03994519162531633;
    coeffs[5][2] = 0.00798609327859495;
  }

  template<class DataType_>
  Oversampling6points5order_32<DataType_>::Oversampling6points5order_32()
  {
    coeffs[0][0] = 0.42685983409379380;
    coeffs[0][1] = 0.07238123511170030;
    coeffs[0][2] = 0.00075893079450573;
    coeffs[1][0] = 0.35831772348893259;
    coeffs[1][1] = 0.20451644554758297;
    coeffs[1][2] = 0.00562658797241955;
    coeffs[2][0] = -0.217009177221292431;
    coeffs[2][1] = 0.20051376594086157;
    coeffs[2][2] = 0.01649541128040211;
    coeffs[3][0] = -0.25112715343740988;
    coeffs[3][1] = 0.04223025992200458;
    coeffs[3][2] = 0.02488727472995134;
    coeffs[4][0] = 0.04166746673533273;
    coeffs[4][1] = -0.06250420114356986;
    coeffs[4][2] = 0.02083473440841799;
    coeffs[5][0] = 0.08349799235675044;
    coeffs[5][1] = -0.04174912841630993;
    coeffs[5][2] = 0.00834987866042734;
  }

  template<class DataType, class Coefficients>
  OversamplingFilter<DataType, Coefficients>::OversamplingFilter()
    :TypedBaseFilter<DataType>(1, 1)
  {
    for(int i = 0; i < Coefficients::points; ++i)
    {
      buffer[i] = 0;
    }
  }

  template<class DataType, class Coefficients>
  void OversamplingFilter<DataType, Coefficients>::process_impl(long size)
  {
    assert(input_sampling_rate * Coefficients::oversampling_factor == output_sampling_rate);
    if(outputs_size[0] < size)
    {
      outputs[0].reset(new DataType[size]);
      outputs_size[0] = size;
    }
    
    for(int i = 0; i < size / Coefficients::oversampling_factor; ++i)
    {
      for(int j = 0; j < Coefficients::points - 1; ++j)
      {
        buffer[j] = buffer[j + 1];
      }
      buffer[Coefficients::points - 1] = converted_inputs[0][i];
      
      DataType even[Coefficients::points / 2];
      for(int j = 0; j < Coefficients::points / 2; ++j)
      {
        even[j] = buffer[Coefficients::points / 2 + j] + buffer[Coefficients::points / 2 - 1 - j];
      }
      DataType odd[Coefficients::points / 2];
      for(int j = 0; j < Coefficients::points / 2; ++j)
      {
        odd[j] = buffer[Coefficients::points / 2 + j] - buffer[Coefficients::points / 2 - 1 - j];
      }
      
      DataType c[Coefficients::order + 1];
      
      for(int j = 0; j < Coefficients::order + 1; j += 2)
      {
        c[j] = 0;
        for(int k = 0; k < Coefficients::points / 2; ++k)
        {
          c[j] += even[k] * coeffs.coeffs[j][k];
        }
      }
      for(int j = 1; j < Coefficients::order + 1; j += 2)
      {
        c[j] = 0;
        for(int k = 0; k < Coefficients::points / 2; ++k)
        {
          c[j] += odd[k] * coeffs.coeffs[j][k];
        }
      }
      
      for (int j = 0; j < Coefficients::oversampling_factor; ++j)
      {
        DataType z = static_cast<DataType>(j) / Coefficients::oversampling_factor - 1 / 2.;
        
        DataType temp = 0;
        for(int k = Coefficients::order; k >= 0; --k)
        {
          temp = temp * z + c[k];
        }
        outputs[0][Coefficients::oversampling_factor * i + j] = temp;
      }
    }
  }
  
  template class Oversampling6points5order_2<float>;
  template class Oversampling6points5order_2<double>;
  template class Oversampling6points5order_4<float>;
  template class Oversampling6points5order_4<double>;
  template class Oversampling6points5order_8<float>;
  template class Oversampling6points5order_8<double>;
  template class Oversampling6points5order_16<float>;
  template class Oversampling6points5order_16<double>;
  template class Oversampling6points5order_32<float>;
  template class Oversampling6points5order_32<double>;
  
  template class OversamplingFilter<float, Oversampling6points5order_2<float> >;
  template class OversamplingFilter<double, Oversampling6points5order_2<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_4<float> >;
  template class OversamplingFilter<double, Oversampling6points5order_4<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_8<float> >;
  template class OversamplingFilter<double, Oversampling6points5order_8<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_16<float> >;
  template class OversamplingFilter<double, Oversampling6points5order_16<double> >;
  template class OversamplingFilter<float, Oversampling6points5order_32<float> >;
  template class OversamplingFilter<double, Oversampling6points5order_32<double> >;
}
