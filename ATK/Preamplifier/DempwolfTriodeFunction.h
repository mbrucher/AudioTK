/**
 * \file DempwolfTriodeFunction.h
 * http://recherche.ircam.fr/pub/dafx11/Papers/76_e.pdf
 */

#ifndef ATK_PREAMPLIFIER_DEMPWOLFTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_DEMPWOLFTRIODEFUNCTION_H

#include <ATK/Utility/fmath.h>

#include <cmath>

namespace ATK
{
  /// A more complex triode model, used with TriodeFilter
  template <typename DataType_>
  class DempwolfTriodeFunction
  {
  private:
    const DataType_ G;
    const DataType_ mu;
    const DataType_ gamma;
    const DataType_ C;

    const DataType_ Gg;
    const DataType_ eta;
    const DataType_ Cg;
    const DataType_ Ig0;
    
    DataType_ CgVbe;
    DataType_ lnCgVbe;
    DataType_ powlnCgVbe;
    DataType_ CVceVbe;
    DataType_ lnCVceVbe;
    DataType_ powlnCVceVbe;
  public:
    /// For non static models
    const DataType_ Cpg;

    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      CgVbe = fmath::exp(Cg * Vbe);
      lnCgVbe = fmath::log(1 + CgVbe) / Cg;
      powlnCgVbe = fmath::pow(lnCgVbe, eta - 1);
      return Ig0 + Gg * lnCgVbe * powlnCgVbe;
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return Gg * eta * (CgVbe / (1 + CgVbe)) * powlnCgVbe;
    }
    
    /// Compute grid current derivative relative to the plate cathode voltage
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return 0;
    }
    
    /// Compute plate current
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      CVceVbe = fmath::exp(C * (Vce / mu + Vbe));
      lnCVceVbe = fmath::log(1 + CVceVbe) / C;
      powlnCVceVbe = fmath::pow(lnCVceVbe, gamma - 1);
      return G * lnCVceVbe * powlnCVceVbe - (Ig0 + Gg * lnCgVbe * powlnCgVbe);
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return G * gamma * (CVceVbe / (1 + CVceVbe)) * powlnCVceVbe - Lb_Vbe(Vbe, Vce);
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return G * gamma * (CVceVbe / (1 + CVceVbe)) * powlnCVceVbe / mu;
    }
    
    /// Constructor
    DempwolfTriodeFunction(DataType_ G, DataType_ mu, DataType_ gamma, DataType_ C, DataType_ Gg, DataType_ eta, DataType_ Cg, DataType_ Ig0, DataType_ Cpg)
    :G(G), mu(mu), gamma(gamma), C(C), Gg(Gg), eta(eta), Cg(Cg), Ig0(Ig0), Cpg(Cpg)
    {
    }

    /// Build a new triode function for a filter (12AX7/ECC83)
    static DempwolfTriodeFunction build_standard_function(DataType_ G = 1.371e-3, DataType_ mu = 83.9, DataType_ gamma = 1.349, DataType_ C = 4.56, DataType_ Gg = 3.263e-4, DataType_ eta = 1.156, DataType_ Cg = 11.99, DataType_ Ig0 = 3.917e-8, DataType_ Cpg = 1.7e-12)
    {
      return DempwolfTriodeFunction(G, mu, gamma, C, Gg, eta, Cg, Ig0, Cpg);
    }

    /// Build a new triode function for a filter (12AX7/ECC83)
    static DempwolfTriodeFunction build_alternate_function_1()
    {
      return DempwolfTriodeFunction(2.242e-3, 103.2, 1.26, 3.40, 6.177e-4, 1.314, 9.901, 8.025e-8, 1.7e-12);
    }

    /// Build a new triode function for a filter (12AX7/ECC83)
    static DempwolfTriodeFunction build_alternate_function_2()
    {
      return DempwolfTriodeFunction(2.173e-3, 100.2, 1.28, 3.19, 5.911e-4, 1.358, 11.76, 4.527e-8, 1.7e-12);
    }

  };
}

#endif
