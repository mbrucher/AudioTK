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

  ID:               atk_tools
  vendor:           Matthieu Brucher
  version:          3.1.0
  name:             ATK Tools
  description:      Tools classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:     atk_core
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_TOOLS
#define ATK_TOOLS

#include <ATK/Tools/ToolsInterface.h>

#include <ATK/Tools/ApplyGainFilter.h>
#include <ATK/Tools/BufferFilter.h>
#include <ATK/Tools/CachedCosinusGeneratorFilter.h>
#include <ATK/Tools/CachedSinusGeneratorFilter.h>
#include <ATK/Tools/DecimationFilter.h>
#include <ATK/Tools/DerivativeFilter.h>
#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Tools/MaxFilter.h>
#include <ATK/Tools/MSFilter.h>
#include <ATK/Tools/MuteSoloBufferFilter.h>
#include <ATK/Tools/OffsetVolumeFilter.h>
#include <ATK/Tools/OneMinusFilter.h>
#include <ATK/Tools/OversamplingFilter.h>
#include <ATK/Tools/PanFilter.h>
#include <ATK/Tools/SinusGeneratorFilter.h>
#include <ATK/Tools/SumFilter.h>
#include <ATK/Tools/TanFilter.h>
#include <ATK/Tools/VolumeFilter.h>
#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>

#endif
