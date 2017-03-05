/**
 * \file DempwolfTriodeFunction.h
 * from Measures and models of real triodes, for the simulation of guitar amplifiers (Cohen and Helie)
 * https://hal.archives-ouvertes.fr/hal-00811215
 */

#ifndef ATK_PREAMPLIFIER_DEMPWOLFTRIODEFUNCTION_H
#define ATK_PREAMPLIFIER_DEMPWOLFTRIODEFUNCTION_H

#include <cmath>
#include <ATK/Utility/fmath.h>

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
    
  public:
    /// For non static models
    const DataType_ Cpg;

    /// Compute grid current
    DataType_ Lb(DataType_ Vbe, DataType_ Vce)
    {
      return Ig0 + Gg * std::pow(std::log(1 + std::exp(Cg * Vbe)) / Cg, eta);
    }
    
    /// Compute grid current derivative relative to the grid cathode voltage
    DataType_ Lb_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return Gg * (std::exp(Cg * Vbe) / (1 + std::exp(Cg * Vbe))) * std::pow(std::log(1 + std::exp(Cg * Vbe)) / Cg, eta - 1);
    }
    
    /// Compute grid current derivative relative to the plate cathode voltage
    DataType_ Lb_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return 0;
    }
    
    /// Compute plate current
    DataType_ Lc(DataType_ Vbe, DataType_ Vce)
    {
      return G * std::pow(std::log(1 + std::exp(C * (Vce / mu + Vbe))) / C, gamma) - Lb(Vbe, Vce);
    }
    
    /// Compute plate current derivative relative to the grid cathode voltage
    DataType_ Lc_Vbe(DataType_ Vbe, DataType_ Vce)
    {
      return G * (std::exp(C * (Vce / mu + Vbe)) / (1 + std::exp(C * (Vce / mu + Vbe)))) * std::pow(std::log(1 + std::exp(C * (Vce / mu +  Vbe))) / C, gamma - 1) - Lb_Vbe(Vbe, Vce);
    }
    
    /// Compute plate current derivative relative to the plate cathode voltage
    DataType_ Lc_Vce(DataType_ Vbe, DataType_ Vce)
    {
      return G * (std::exp(C * (Vce / mu + Vbe)) / (1 + std::exp(C * (Vce / mu + Vbe)))) * std::pow(std::log(1 + std::exp(C * (Vce / mu +  Vbe))) / C, gamma - 1) / mu;
    }
    
    /// Constructor
    DempwolfTriodeFunction(DataType_ G, DataType_ mu, DataType_ gamma, DataType_ C, DataType_ Gg, DataType_ eta, DataType_ Cg, DataType_ Ig0, DataType_ Cpg)
    :G(G), mu(mu), gamma(gamma), C(C), Gg(Gg), eta(eta), Cg(Cg), Ig0(Ig0), Cpg(Cpg)
    {
    }

    /// Build a new triode function for a filter (12AX7/ECC83)
    static DempwolfTriodeFunction build_standard_function()
    {
      return DempwolfTriodeFunction(1.371e-3, 83.9, 1.349, 4.56, 3.263e-4, 1.156, 11.99, 3.917e-8, 1.7e-12);
    }

  };
}

#endif
