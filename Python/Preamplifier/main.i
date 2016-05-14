#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Preamplifier", docstring="Python interface to ATK Preamplifier module") Preamplifier

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "TransistorClassAFilter.i"
%include "TriodeFilter.i"

#endif
