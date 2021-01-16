/**
 * \file EnhancedKorenTriodeFunction.h
 * from Measures and models of real triodes, for the simulation of guitar amplifiers (Cohen and Helie)
 * https://hal.archives-ouvertes.fr/hal-00811215
 */

#ifndef ATK_PREAMPLIFIER_ENHANCEDKORENTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_ENHANCEDKORENTRIODEFUNCTION_H

#include <ATK/Utility/fmath.h>

#include <cmath>

namespace ATK
{
  /// A more complex triode model, used with TriodeFilter
  template <typename DataType_>
  class EnhancedKorenTriodeFunction
  {
  private:
    const DataType_ a;
    const DataType_ b;
    const DataType_ c;
    const DataType_ Vphi;
    const DataType_ gamma;

    const DataType_ mu;
    const DataType_ Kp;
    const DataType_ Vct;
    const DataType_ Kvb;
    const DataType_ Kvb2;
    const DataType_ Kg;
    const DataType_ Ex;
    
    DataType_ exp_comp;
    DataType_ ln_exp_comp_1;
    DataType_ first_term;
    
    DataType_ tmp;
    DataType_ E2;
    DataType_ lnE2;
    DataType_ E1;
    DataType_ E1_Ex1;
    
  public:
    /// For non static models
    const DataType_ Cpg;

    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      exp_comp = fmath::exp(a * (Vbe + Vphi));
      ln_exp_comp_1 = fmath::log(1 + exp_comp);
      first_term = fmath::pow(ln_exp_comp_1, gamma - 1);
      return first_term * ln_exp_comp_1 * (1/(b * Vce + 1) + 1/c);
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return (1/(b * Vce + 1) + 1/c) * gamma * first_term / (1+exp_comp) * a * exp_comp;
    }
    
    /// Compute grid current derivative relative to the plate cathode voltage
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return - first_term * ln_exp_comp_1 * b / ((b * Vce + 1)*(b * Vce + 1));
    }
    
    /// Compute plate current
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        tmp = std::sqrt(Kvb + Vce * Kvb2 + Vce * Vce);
        E2 = 1 + fmath::exp(Kp * (1 / mu + (Vbe + Vct) / tmp));
        lnE2 = fmath::log(E2);
        E1 = Vce / Kp * lnE2;
        E1_Ex1 = fmath::pow(E1, Ex - 1);
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
        DataType_ E1p = 1 / Kp * lnE2 - Vce / Kp / E2 * (E2 - 1) * Kp * (Vbe + Vct) * (2 * Vce + Kvb2) / 2 / (tmp * (Kvb + Vce * Kvb2 + Vce * Vce));
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    /// Constructor
    EnhancedKorenTriodeFunction(DataType_ a, DataType_ b, DataType_ c, DataType_ Vphi, DataType_ gamma, DataType_ mu, DataType_ Kp, DataType_ Vct, DataType_ Kvb, DataType_ Kvb2, DataType_ Kg, DataType_ Ex, DataType_ Cpg)
    :a(a), b(b), c(c), Vphi(Vphi), gamma(gamma), mu(mu), Kp(Kp), Vct(Vct), Kvb(Kvb), Kvb2(Kvb2), Kg(Kg), Ex(Ex), Cpg(Cpg)
    {
    }

    /// Build a new triode function for a filter (12AX7/ECC83)
    static EnhancedKorenTriodeFunction build_standard_function(DataType_ a = 17.32, DataType_ b = 21238.8, DataType_ c = 163757, DataType_ Vphi = -0.2227, DataType_ gamma = 1.444, DataType_ mu = 105, DataType_ Kp = 578.2, DataType_ Vct = 0.378, DataType_ Kvb = 50, DataType_ Kvb2 = 18.8, DataType_ Kg = 1335, DataType_ Ex = 1.277, DataType_ Cpg = 1.7e-12)
    {
      return EnhancedKorenTriodeFunction(a, b, c, Vphi, gamma, mu, Kp, Vct, Kvb, Kvb2, Kg, Ex, Cpg);
    }

  };
}

#endif
