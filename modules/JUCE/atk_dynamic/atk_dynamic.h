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

  ID:               atk_dynamic
  vendor:           Matthieu Brucher
  version:          3.1.0
  name:             ATK dynamic
  description:      Dynamic classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:     atk_core
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_DYNAMIC
#define ATK_DYNAMIC

#include <ATK/Dynamic/AttackReleaseFilter.h>
#include <ATK/Dynamic/AttackReleaseHysteresisFilter.h>
#include <ATK/Dynamic/GainColoredCompressorFilter.h>
#include <ATK/Dynamic/GainColoredExpanderFilter.h>
#include <ATK/Dynamic/GainCompressorFilter.h>
#include <ATK/Dynamic/GainExpanderFilter.h>
#include <ATK/Dynamic/GainFilter.h>
#include <ATK/Dynamic/GainLimiterFilter.h>
#include <ATK/Dynamic/GainMaxColoredExpanderFilter.h>
#include <ATK/Dynamic/GainMaxCompressorFilter.h>
#include <ATK/Dynamic/GainMaxExpanderFilter.h>
#include <ATK/Dynamic/GainSwellFilter.h>
#include <ATK/Dynamic/PowerFilter.h>
#include <ATK/Dynamic/RelativePowerFilter.h>

#endif
