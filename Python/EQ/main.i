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

%module(package="EQ", docstring="Python interface to ATK EQ module") EQ

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"
%include "ChamberlinFilter.i"
%include "IIRFilter.i"
%include "SecondOrderFilter.i"
%include "LinkwitzRileyFilter.i"
%include "RIAAFilter.i"
%include "RobertBristowJohnsonFilter.i"
%include "SecondOrderSVFFilter.i"
%include "BesselFilter.i"
%include "ButterworthFilter.i"
%include "Chebyshev1Filter.i"
%include "Chebyshev2Filter.i"
%include "CustomIIRFilter.i"

%include "FIRFilter.i"
%include "CustomFIRFilter.i"
%include "RemezBasedFilter.i"

%include "TimeVaryingIIRFilter.i"
%include "TimeVaryingSecondOrderFilter.i"
%include "TimeVaryingSecondOrderSVFFilter.i"

%include "PedalToneStackFilter.i"
%include "ToneStackFilter.i"

#endif
