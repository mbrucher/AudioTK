#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Special", docstring="Python interface to ATK Special module") Special

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"

%include "ConvolutionFilter.i"

#endif
