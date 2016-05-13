/**
 * \file EnhancedKorenTriodeFunction.h
 * from Measures and models of real triodes, for the simulation of guitar amplifiers (Cohen and Helie)
 * https://hal.archives-ouvertes.fr/hal-00811215
 */

#ifndef ATK_PREAMPLIFIER_ENHANCEDKORENTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_ENHANCEDKORENTRIODEFUNCTION_H

#include <cmath>

namespace ATK
{
  /// A simplified tube model
  template <typename DataType_>
  class EnhancedKorenTriodeFunction
  {
  protected:
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
    DataType_ first_component;
    
    DataType_ tmp;
    DataType_ E2;
    DataType_ lnE2;
    DataType_ E1;
    DataType_ E1_Ex1;
    
  public:
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      exp_comp = std::exp(a * Vbe + Vphi);
      ln_exp_comp_1 = std::log(1 + exp_comp);
      first_component = std::pow(ln_exp_comp_1, gamma - 1);
      return first_component * ln_exp_comp_1 * (1/(b * Vce + 1) + 1/c);
    }
    
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return (1/(b * Vce + 1) + 1/c) * first_component * 1/(1+exp_comp) * a * exp_comp;
    }
    
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return - first_component * ln_exp_comp_1 * -b / ((b * Vce + 1)*(b * Vce + 1));
    }
    
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      if (Vce > 0)
      {
        tmp = std::sqrt(Kvb + Vce * Kvb2 + Vce * Vce);
        E2 = 1 + std::exp(Kp * (1 / mu + (Vbe + Vct) / tmp));
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
        DataType_ E1p = 1 / Kp * lnE2 - Vce / Kp / E2 * (E2 - 1) * Kp * (Vbe + Vct) * (2 * Vce + Kvb2) / 2 / (tmp * (Kvb + Vce * Vce));
        return 2 * Ex / Kg * E1_Ex1 * E1p;
      }
      return 0;
    }
    
    EnhancedKorenTriodeFunction(DataType_ a, DataType_ b, DataType_ c, DataType_ Vphi, DataType_ gamma, DataType_ mu, DataType_ Kp, DataType_ Vct, DataType_ Kvb, DataType_ Kvb2, DataType_ Kg, DataType_ Ex)
    :a(a), b(b), c(c), Vphi(Vphi), gamma(gamma), mu(mu), Kp(Kp), Vct(Vct), Kvb(Kvb), Kvb2(Kvb2), Kg(Kg), Ex(Ex)
    {
    }

    static EnhancedKorenTriodeFunction build_standard_function()
    {
      return EnhancedKorenTriodeFunction(17.32, 21238.8, 163757, -0.2227, 1.444, 105, 578.2, 0.378, 50, 18.8, 1335, 1.277);
    }

  };
}

#endif
