#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Reverberation", docstring="Python interface to ATK Reverberation module") Reverberation

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"

%include "AllPassReverbFilter.i"
%include "LowPassReverbFilter.i"


#endif
