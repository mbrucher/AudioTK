/**
 * \file ModifiedMunroPiazzaTriodeFunction.h
 * From http://www.duncanamps.com/spice/valves/dm12ax7s.inc
 */

#ifndef ATK_PREAMPLIFIER_MODIFIEDMUNROPIAZZATRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_MODIFIEDMUNROPIAZZATRIODEFUNCTION_H

#include <ATK/Utility/fmath.h>

#include <cmath>
#include <iostream>

namespace ATK
{
  /// Tube model, used with TriodeFilter from Munro and Piazza
  template <typename DataType_>
  class ModifiedMunroPiazzaTriodeFunction
  {
  private:
    const DataType_ mu;
    const DataType_ K;
    const DataType_ Kp;
    const DataType_ Kvb;
    const DataType_ Kg;
    const DataType_ sigma;
    const DataType_ sqrt_sigma;
    
    DataType_ sqrt_muvbe;
    DataType_ E1;
    DataType_ sqrt_E1;
    
  public:
    /// For non static models
    const DataType_ Cpg;
    
    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      if(mu + Vbe > 0)
      {
        sqrt_muvbe = std::sqrt(sigma + (mu + Vbe) * (mu + Vbe) * (mu + Vbe));
        return K * (sqrt_muvbe - sqrt_sigma);
      }
      return 0;
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if(mu + Vbe > 0)
      {
        return 3 * K * (mu + Vbe) * (mu + Vbe) / (2 * sqrt_muvbe);
      }
      return 0;
    }
    
    /// Compute grid current derivative relative to the plate cathode voltage
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return 0;
    }
    
    /// Compute plate current
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      E1 = Kp + Vce + Kg * Vbe;
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        sqrt_E1 = std::sqrt(E1);
        return Vce / 5 * Kvb * sqrt_E1 * E1;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        return Kg * Vce / 5 * Kvb * sqrt_E1 * 1.5F;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        return Kvb * sqrt_E1 * E1 / 5 + Vce / 5 * Kvb * sqrt_E1 * 1.5F;
      }
      return 0;
    }
    
    /// Constructor
    ModifiedMunroPiazzaTriodeFunction(DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ sigma, DataType_ Cpg)
    :mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), sigma(sigma), sqrt_sigma(std::sqrt(sigma)), Cpg(Cpg)
    {
    }
    
    /// Build a new triode function for a filter (12AX7/ECC83)
    static ModifiedMunroPiazzaTriodeFunction build_standard_function(DataType_ mu = 0.2, DataType_ K = 5e-6, DataType_ Kp = 45, DataType_ Kvb = 1.147e-6, DataType_ Kg = 95.43, DataType_ sigma = 1, DataType_ Cpg = 1.7e-12)
    {
      return ModifiedMunroPiazzaTriodeFunction(mu, K, Kp, Kvb, Kg, sigma, Cpg);
    }
  };
}

#endif
