/*
 ==============================================================================
 
 This file is part of the ATK library.
 Copyright (c) 2017 - Matthieu Brucher
 
 ATK is an open source library subject to the BSD licnse.
 
 ==============================================================================
 */

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               atk_eq
  vendor:           Matthieu Brucher
  version:          2.2.3
  name:             ATK EQ
  description:      EQ classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:     atk_core
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_EQ
#define ATK_EQ

#include <ATK/EQ/BesselFilter.h>
#include <ATK/EQ/ButterworthFilter.h>
#include <ATK/EQ/ChamberlinFilter.h>
#include <ATK/EQ/Chebyshev1Filter.h>
#include <ATK/EQ/Chebyshev2Filter.h>
#include <ATK/EQ/CustomFIRFilter.h>
#include <ATK/EQ/CustomIIRFilter.h>
#include <ATK/EQ/EQInterface.h>
#include <ATK/EQ/FIRFilter.h>
#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/helpers.h>
#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/LinkwitzRileyFilter.h>
#include <ATK/EQ/PedalToneStackFilter.h>
#include <ATK/EQ/RIAAFilter.h>
#include <ATK/EQ/RobertBristowJohnsonFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>
#include <ATK/EQ/SecondOrderSVFFilter.h>
#include <ATK/EQ/TimeVaryingIIRFilter.h>
#include <ATK/EQ/TimeVaryingSecondOrderFilter.h>
#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

#if (ATK_USE_FFTW == 1) or (ATK_USE_IPP == 1)
# include <ATK/EQ/RemezBasedFilter.h>
#endif

#endif
