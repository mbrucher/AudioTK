
%{
#include <ATK/Core/BaseFilter.h>
#include <ATK/Utility/FlushToZero.h>
%}

%define ATKProperty(class_name, property_name, get_property_name, set_property_name)
%extend class_name{
      %pythoncode %{
         __swig_getmethods__["property_name"] = get_property_name
         __swig_setmethods__["property_name"] = set_property_name
         property_name = property(get_property_name, set_property_name)
      %}
 }
%enddef

%define ATKgetProperty(class_name, property_name, get_property_name)
%extend class_name{
      %pythoncode %{
         __swig_getmethods__["property_name"] = get_property_name
         property_name = property(get_property_name)
      %}
 }
%enddef

namespace ATK
{
  class BaseFilter
  {
  public:
    void set_input_port(int input_port, BaseFilter* filter, int output_port);
    void set_input_sampling_rate(int rate);
    void set_output_sampling_rate(int rate);
    int get_input_sampling_rate();
    int get_output_sampling_rate();
    
    void set_latency(uint64_t latency);
    uint64_t get_latency() const;
    uint64_t get_global_latency() const;

    %extend {
      void process(long size)
      {
        ATK::FlushToZero flusher;
        $self->process(size);
		  }
    }
  };
  
  ATKProperty(BaseFilter, input_sampling_rate, get_input_sampling_rate, set_input_sampling_rate);
  ATKProperty(BaseFilter, output_sampling_rate, get_output_sampling_rate, set_output_sampling_rate);
}

%{
#include <boost/align/aligned_allocator.hpp>
%}

%include <std_vector.i>

%template(FloatVector) std::vector<float, boost::alignment::aligned_allocator<float, 32>>;
%template(DoubleVector) std::vector<double, boost::alignment::aligned_allocator<double, 32>>;

%typemap(out) std::vector<float, boost::alignment::aligned_allocator<float, 32>> {
    npy_intp length = $1.size();
    $result = PyArray_SimpleNew(1, &length, NPY_FLOAT);
    memcpy(PyArray_DATA((PyArrayObject*)$result),$1.data(),sizeof(float)*length);
}
%typemap(out) std::vector<double, boost::alignment::aligned_allocator<double, 32>> {
    npy_intp length = $1.size();
    $result = PyArray_SimpleNew(1, &length, NPY_DOUBLE);
    memcpy(PyArray_DATA((PyArrayObject*)$result),$1.data(),sizeof(double)*length);
}
