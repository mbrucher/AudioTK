#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API

#include <complex>

%}
%include "numpy.i"

%numpy_typemaps(std::complex<float>, NPY_CFLOAT , int)
%numpy_typemaps(std::complex<double>, NPY_CDOUBLE, int)

%fragment("NumPy_Fragments");

%init
%{
import_array();
%}

%module(package="Core", docstring="Python interface to ATK Core module") Core

%nodefaultdtor;
%nodefaultctor;

%include "BaseFilter.i"
%include "PointerFilter.i"
%include "ComplexConvertFilter.i"
%include "PipelineGlobalSinkFilter.i"

#endif
