#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API

#include <complex>
%}

%module(package="Tools", docstring="Python interface to ATK Tools module") Tools

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "ApplyGainFilter.i"
%include "BufferFilter.i"
%include "CachedCosinusGeneratorFilter.i"
%include "CachedSinusGeneratorFilter.i"
%include "DecimationFilter.i"
%include "DerivativeFilter.i"
%include "DryWetFilter.i"
%include "MaxFilter.i"
%include "MSFilter.i"
%include "OffsetVolumeFilter.i"
%include "OneMinusFilter.i"
%include "OversamplingFilter.i"
%include "PanFilter.i"
%include "SinusGeneratorFilter.i"
%include "SumFilter.i"
%include "TanFilter.i"
%include "VolumeFilter.i"
%include "WhiteNoiseGeneratorFilter.i"

#endif
