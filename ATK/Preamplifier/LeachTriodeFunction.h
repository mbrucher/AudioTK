/**
 * \file LeachTriodeFunction.h
 */

#ifndef ATK_PREAMPLIFIER_LEACHTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_LEACHTRIODEFUNCTION_H

#include <cmath>
#include <ATK/Utility/fmath.h>

namespace ATK
{
  /// A simplified tube model, used with TriodeFilter
  template <typename DataType_>
  class LeachTriodeFunction
  {
  private:
    const DataType_ mu;
    const DataType_ K;
    const DataType_ Rgk;
    const DataType_ Vgamma;
    
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
      return (Vbe - Vgamma) / Rgk;
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return 1 / Rgk;
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return 0;
    }
    
    /// Constructor
    LeachTriodeFunction(DataType_ mu, DataType_ K, DataType_ Rgk, DataType_ Vgamma, DataType_ Cpg)
    :mu(mu), K(K), Rgk(Rgk), Vgamma(Vgamma), Cpg(Cpg)
    {
    }
    
    /// Build a new triode function for a filter (12AX7/ECC83)
    static LeachTriodeFunction build_standard_function()
    {
      return LeachTriodeFunction(88.5, 1.73e-6, 20e3, 0.6, 1.7e-12);
    }

  };
}

#endif
