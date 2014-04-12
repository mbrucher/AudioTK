#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Tools", docstring="Python interface to ATK Tools module") EQ

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "IIRFilter.i"
%include "SecondOrderFilter.i"
%include "BesselFilter.i"
%include "ButterworthFilter.i"
%include "Chebyshev1Filter.i"
%include "Chebyshev2Filter.i"

#endif
