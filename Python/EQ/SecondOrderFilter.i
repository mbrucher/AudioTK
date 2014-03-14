
%{
#include <ATK/EQ/SecondOrderFilter.h>
#include <ATK/EQ/IIRFilter.h>
%}

%rename(BandPassFilterFloat) IIRFilter<BandPassCoefficients<float> >;
