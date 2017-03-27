#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
%include "numpy.i"
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
%include "PipelineGlobalSinkFilter.i"

#endif
