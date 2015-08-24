#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Dynamic", docstring="Python interface to ATK Dynamic module") Dynamic

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "AttackReleaseFilter.i"
%include "GainColoredCompressorFilter.i"
%include "GainColoredExpanderFilter.i"
%include "GainCompressorFilter.i"
%include "GainExpanderFilter.i"
%include "GainFractionalCompressorFilter.i"
%include "GainFractionalExpanderFilter.i"
%include "GainLimiterFilter.i"
%include "GainMaxExpanderFilter.i"
%include "GainSwellFilter.i"
%include "PowerFilter.i"
%include "RelativePowerFilter.i"

#endif
