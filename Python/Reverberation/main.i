#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Reverberation", docstring="Python interface to ATK Reverberation module") Delay

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"

#endif
