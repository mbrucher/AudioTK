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
  static name<T, T2<T> >* build_standard_filter(T Rp=200e3, T Rg=220e3, T Ro=220e3, T Rk=1e3, T VBias=300, T Co=22e-9, T Ck=1.e-6)
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_standard_filter());
  }
}
%enddef

%define PreampExtendAlternate(name, T, T2, alternate)
%extend name<T, T2<T> > {
  %newobject alternate;
  static name<T, T2<T> >* alternate(T Rp=200e3, T Rg=220e3, T Ro=220e3, T Rk=1e3, T VBias=300, T Co=22e-9, T Ck=1.e-6)
  {
    return new name<T, T2<T> >(name<T, T2<T> >::build_alternate_filter<T2<T>::alternate>(Rp, Rg, Ro, Rk, VBias, Co, Ck));
  }
}
%enddef


%include "FollowerTransistorClassAFilter.i"
%include "TransistorClassAFilter.i"
%include "TriodeFilter.i"
%include "Triode2Filter.i"

#endif
