#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
%include "../Core/numpy.i"
%fragment("NumPy_Fragments");

%init
%{
import_array();
%}

%module(package="Adaptive", docstring="Python interface to ATK Adaptive module") Adaptive

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "RLSFilter.i"

#endif
