#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="IO", docstring="Python interface to ATK IO module") IO

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "InWavFilter.i"

#endif
