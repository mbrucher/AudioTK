/*
 ==============================================================================
 
 This file is part of the ATK library.
 Copyright (c) 2017 - Matthieu Brucher
 
 ATK is an open source library subject to the BSD licnse.
 
 ==============================================================================
 */

#include "atk_eq.h"

#include <ATK/EQ/BesselFilter.cpp>
#include <ATK/EQ/ButterworthFilter.cpp>
#include <ATK/EQ/ChamberlinFilter.cpp>
#include <ATK/EQ/Chebyshev1Filter.cpp>
#include <ATK/EQ/Chebyshev2Filter.cpp>
#include <ATK/EQ/CustomFIRFilter.cpp>
#include <ATK/EQ/CustomIIRFilter.cpp>
#include <ATK/EQ/FIRFilter.cpp>
#include <ATK/EQ/FourthOrderFilter.cpp>
#include <ATK/EQ/helpers.cpp>
#include <ATK/EQ/IIRFilter.cpp>
#include <ATK/EQ/LinkwitzRileyFilter.cpp>
#include <ATK/EQ/PedalToneStackFilter.cpp>
#include <ATK/EQ/RIAAFilter.cpp>
#include <ATK/EQ/RobertBristowJohnsonFilter.cpp>
#include <ATK/EQ/SecondOrderFilter.cpp>
#include <ATK/EQ/SecondOrderSVFFilter.cpp>
#include <ATK/EQ/TimeVaryingIIRFilter.cpp>
#include <ATK/EQ/TimeVaryingSecondOrderFilter.cpp>
#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.cpp>
#include <ATK/EQ/ToneStackFilter.cpp>

#if (ATK_USE_FFTW == 1) or (ATK_USE_IPP == 1)
# include <ATK/EQ/RemezBasedFilter.cpp>
#endif
