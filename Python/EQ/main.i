#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
%include "../Core/numpy.i"
%fragment("NumPy_Fragments");

%module(package="EQ", docstring="Python interface to ATK EQ module") EQ

%nodefaultdtor;
%nodefaultctor;

%{
#include <boost/align/aligned_allocator.hpp>
%}

%include <std_vector.i>

%template(FloatVector) std::vector<float, boost::alignment::aligned_allocator<float, 32>>;
%template(DoubleVector) std::vector<double, boost::alignment::aligned_allocator<double, 32>>;

%typemap(out) std::vector<float, boost::alignment::aligned_allocator<float, 32>> {
    int length = $1.size();
    $result = PyArray_FromDims(1, &length, NPY_FLOAT);
    memcpy(PyArray_DATA($result),&((*(&$1))[0]),sizeof(float)*length);
}
%typemap(out) std::vector<double, boost::alignment::aligned_allocator<double, 32>> {
    int length = $1.size();
    $result = PyArray_FromDims(1, &length, NPY_DOUBLE);
    memcpy(PyArray_DATA($result),&((*(&$1))[0]),sizeof(double)*length);
}

%include "../Core/BaseFilter.i"
%include "ChamberlinFilter.i"
%include "IIRFilter.i"
%include "SecondOrderFilter.i"
%include "LinkwitzRileyFilter.i"
%include "RobertBristowJohnsonFilter.i"
%include "SecondOrderSVFFilter.i"
%include "BesselFilter.i"
%include "ButterworthFilter.i"
%include "Chebyshev1Filter.i"
%include "Chebyshev2Filter.i"
%include "CustomIIRFilter.i"

%include "FIRFilter.i"
%include "CustomFIRFilter.i"

%include "TimeVaryingIIRFilter.i"
%include "TimeVaryingSecondOrderFilter.i"
%include "TimeVaryingSecondOrderSVFFilter.i"

%include "PedalToneStackFilter.i"
%include "ToneStackFilter.i"

#endif
