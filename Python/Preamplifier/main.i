#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}

%module(package="Preamplifier", docstring="Python interface to ATK Preamplifier module") Preamplifier

%nodefaultdtor;
%nodefaultctor;

%include "../Core/BaseFilter.i"

%define PreampExtendSimple(name, T)
%extend name<T> {
  %newobject build_standard_filter;
  static name<T>* build_standard_filter()
  {
    return new name<T>(name<T>::build_standard_filter());
  }
}
%enddef

%define PreampExtend(name, T, T2)
%extend name<T, T2<T> > {
  %newobject build_standard_filter;
  static name<T, T2<T> >* build_standard_filter()
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_standard_filter());
  }
}
%enddef

%define PreampExtendAlternate(name, T, T2, alternate)
%extend name<T, T2<T> > {
  %newobject alternate;
  static name<T, T2<T> >* alternate()
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_alternate_filter<T2<T>::alternate>());
  }
}
%enddef


%include "FollowerTransistorClassAFilter.i"
%include "TransistorClassAFilter.i"
%include "TriodeFilter.i"
%include "Triode2Filter.i"

#endif
