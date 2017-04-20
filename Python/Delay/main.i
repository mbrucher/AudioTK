#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API

#include <complex>
%}

%module(package="Delay", docstring="Python interface to ATK Delay module") Delay

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "FixedDelayLineFilter.i"
%include "HadamardFeedbackDelayNetworkFilter.i"
%include "MultipleUniversalFixedDelayLineFilter.i"
%include "UniversalFixedDelayLineFilter.i"
%include "UniversalVariableDelayLineFilter.i"
%include "VariableDelayLineFilter.i"

#endif
