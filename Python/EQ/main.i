#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
/*%include "numpy.i"
%fragment("NumPy_Fragments");
%{
  const int DataTypeKind = NPY_FLOAT;
  const int CheckTypeKind = NPY_INT;
  %}
%init %{
  import_array();
  %}
*/

%module(package="EQ", docstring="Python interface to ATK EQ module") EQ

%nodefaultdtor;
%nodefaultctor;

%include "SecondOrderFilter.i"

#endif
