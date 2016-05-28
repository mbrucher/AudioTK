/**
 * \file KorenTriodeFunction.h
 * Heavily inspired by Simulation of a guitar amplifier stage for several triode models (Cohen and Helie)
 */

#ifndef ATK_PREAMPLIFIER_KORENTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_KORENTRIODEFUNCTION_H

#include <cmath>
#include <ATK/Utility/fmath.h>

namespace ATK
{
  /// A simplified tube model, used with TriodeFilter
  template <typename DataType_>
  class KorenTriodeFunction
  {
  private:
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
    
    fmath::PowGenerator Ex_1;
    
  public:
    /// For non static models
    const DataType_ Cpg;
    
    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      if(mu * Vbe + Vce > 0)
        return K * std::sqrt(mu * Vbe + Vce) * (mu * Vbe + Vce);
      return 0;
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
      {
        return K * mu * 1.5 * std::sqrt(mu * Vbe + Vce);
      }
      return 0;
    }
    
    /// Compute grid current derivative relative to the plate cathode voltage
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (mu * Vbe + Vce > 0)
      {
        return K * 1.5 * std::sqrt(mu * Vbe + Vce);
      }
      return 0;
    }
    
    /// Compute plate current
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        tmp = std::sqrt(Kvb + Vce * Vce);
        E2 = 1 + fmath::exp(Kp * (1 / mu + Vbe / tmp));
        lnE2 = std::log(E2);
        E1 = Vce / Kp * lnE2;
        E1_Ex1 = std::pow(E1, Ex - 1);
        return 2 / Kg * E1_Ex1 * E1;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E1p = Vce / Kp / E2 * (E2 - 1) * Kp / tmp;
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        DataType_ E1p = 1 / Kp * lnE2 - Vce / Kp / E2 * (E2 - 1) * Kp * Vbe * Vce / (tmp * (Kvb + Vce * Vce));
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    /// Constructor
    KorenTriodeFunction(DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Ex, DataType_ Cpg)
    :mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), Ex(Ex), Ex_1(Ex - 1), Cpg(Cpg)
    {
    }
    
    /// Build a new triode function for a filter (12AX7/ECC83)
    static KorenTriodeFunction build_standard_function()
    {
      return KorenTriodeFunction(100, 1.73e-6, 600, 300, 1060, 1.4, 1.7e-12);
    }

  };
}

#endif
