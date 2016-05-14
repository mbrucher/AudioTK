#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Distortion", docstring="Python interface to ATK Distortion module") Distortion

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "DiodeClipperFilter.i"
%include "SimpleOverdriveFilter.i"
%include "SD1OverdriveFilter.i"
%include "SVFSD1OverdriveFilter.i"

#endif
