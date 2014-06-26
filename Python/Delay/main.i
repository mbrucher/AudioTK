#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Delay", docstring="Python interface to ATK Delay module") Delay

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "FixedDelayLineFilter.i"
%include "UniversalFixedDelayLineFilter.i"

#endif
