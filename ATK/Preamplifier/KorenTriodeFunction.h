/**
 * \file KorenTriodeFunction.h
 * Heavily inspired by Simulation of a guitar amplifier stage for several triode models (Cohen and Helie)
 */

#ifndef ATK_PREAMPLIFIER_KORENTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_KORENTRIODEFUNCTION_H

#include <cmath>

namespace ATK
{
  /// A simplified tube model
  template <typename DataType_>
  class KorenTriodeFunction
  {
  protected:
    const DataType_ mu;
    const DataType_ K;
    const DataType_ Kp;
    const DataType_ Kvb;
    const DataType_ Kg;
    const DataType_ Ex;
    
    DataType_ tmp;
    DataType_ E2;
    DataType_ lnE2;
    DataType_ E1;
    DataType_ E1_Ex1;
    
  public:
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      if(mu * Vbe + Vce > 0)
        return K * std::sqrt(mu * Vbe + Vce) * (mu * Vbe + Vce);
      return 0;
    }
    
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
      {
        return K * mu * 1.5 * std::sqrt(mu * Vbe + Vce);
      }
      return 0;
    }
    
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
      {
        return K * 1.5 * std::sqrt(mu * Vbe + Vce);
      }
      return 0;
    }
    
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        tmp = std::sqrt(Kvb + Vce * Vce);
        E2 = 1 + std::exp(Kp * (1 / mu + Vbe / tmp));
        lnE2 = std::log(E2);
        E1 = Vce / Kp * lnE2;
        E1_Ex1 = std::pow(E1, Ex - 1);
        return 2 / Kg * E1_Ex1 * E1;
      }
      return 0;
    }
    
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E1p = Vce / Kp / E2 * (E2 - 1) * Kp / tmp;
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E1p = 1 / Kp * lnE2 - Vce / Kp / E2 * (E2 - 1) * Kp * Vbe * Vce / (tmp * (Kvb + Vce * Vce));
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    KorenTriodeFunction(DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Ex)
    :mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), Ex(Ex)
    {
    }
    
  };
}

#endif
