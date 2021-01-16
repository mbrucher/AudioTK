/**
 * \file MunroPiazzaTriodeFunction.h
 * From http://www.duncanamps.com/spice/valves/dm12ax7s.inc
 */

#ifndef ATK_PREAMPLIFIER_MUNROPIAZZATRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_MUNROPIAZZATRIODEFUNCTION_H

#include <ATK/Utility/fmath.h>

#include <cmath>

namespace ATK
{
  /// Tube model, used with TriodeFilter from Munro and Piazza
  template <typename DataType_>
  class MunroPiazzaTriodeFunction
  {
  private:
    const DataType_ mu;
    const DataType_ K;
    const DataType_ Kp;
    const DataType_ Kvb;
    const DataType_ Kg;
    
  public:
    /// For non static models
    const DataType_ Cpg;
    
    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      if(mu + Vbe > 0)
      {
        return K * std::sqrt(mu + Vbe) * (mu + Vbe);
      }
      return 0;
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      if(mu + Vbe > 0)
      {
        return K * 1.5F * std::sqrt(mu + Vbe);
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
      auto E1 = Kp + Vce + Kg * Vbe;
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        return Vce / 5 * Kvb * std::sqrt(E1) * E1;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      auto E1 = Kp + Vce + Kg * Vbe;
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        return Kg * Vce / 5 * Kvb * std::sqrt(E1) * 1.5F;
      }
      return 0;
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      auto E1 = Kp + Vce + Kg * Vbe;
      if (E1 > 0 && Vbe >= 0 && Vbe <= 5)
      {
        return Kvb * std::sqrt(E1) * E1 / 5 + Vce / 5 * Kvb * std::sqrt(E1) * 1.5F;
      }
      return 0;
    }
    
    /// Constructor
    MunroPiazzaTriodeFunction(DataType_ mu, DataType_ K, DataType_ Kp, DataType_ Kvb, DataType_ Kg, DataType_ Cpg)
    :mu(mu), K(K), Kp(Kp), Kvb(Kvb), Kg(Kg), Cpg(Cpg)
    {
    }
    
    /// Build a new triode function for a filter (12AX7/ECC83)
    static MunroPiazzaTriodeFunction build_standard_function(DataType_ mu = 0.2, DataType_ K = 5e-6, DataType_ Kp = 45, DataType_ Kvb = 1.147e-6, DataType_ Kg = 95.43, DataType_ Cpg = 1.7e-12)
    {
      return MunroPiazzaTriodeFunction(mu, K, Kp, Kvb, Kg, Cpg);
    }

  };
}

#endif
