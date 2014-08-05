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
%include "GainCompressorFilter.i"
%include "GainExpanderFilter.i"
%include "GainLimiterFilter.i"
%include "PowerFilter.i"

#endif
