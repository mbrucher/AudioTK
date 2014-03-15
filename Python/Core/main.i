#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
%include "numpy.i"
%fragment("NumPy_Fragments");
%{
  const int DataTypeKind = NPY_FLOAT;
  const int CheckTypeKind = NPY_INT;
%}
%init %{
  import_array();
%}


%module(package="Core", docstring="Python interface to ATK Core module") Core

%nodefaultdtor;
%nodefaultctor;

%include "PointerFilter.i"

#endif
