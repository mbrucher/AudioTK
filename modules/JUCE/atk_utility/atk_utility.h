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

  ID:               atk_utility
  vendor:           Matthieu Brucher
  version:          2.2.3
  name:             ATK utilities
  description:      Utility classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_UTILITY
#define ATK_UTILITY

#include <ATK/config.h>

#include <ATK/Utility/exp.h>
#include <ATK/Utility/fmath.h>
#include <ATK/Utility/FlushToZero.h>

#if (ATK_USE_FFTW == 1) or (ATK_USE_IPP == 1)
#include <ATK/Utility/FFT.h>
#endif

#endif
