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

  ID:               atk_core
  vendor:           Matthieu Brucher
  version:          2.2.0
  name:             ATK core
  description:      Core classes for ATK
  website:          http://www.audio-tk.com/
  license:          BSD

  dependencies:     atk_utility
  OSXFrameworks:
  iOSFrameworks:

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#ifndef ATK_CORE
#define ATK_CORE

#include <ATK/Core/BaseFilter.h>
#include <ATK/Core/ComplexConvertFilter.h>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutCircularPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/PipelineGlobalSinkFilter.h>
#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/Utilities.h>

#endif
