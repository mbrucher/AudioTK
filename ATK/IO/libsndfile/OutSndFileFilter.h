/**
 * \file OutSndFileFilter.h
 */

#ifndef ATK_IO_OUTSNDFILEFILTER_H
#define ATK_IO_OUTSNDFILEFILTER_H

#include <sndfile.hh>
#include <boost/scoped_ptr.hpp>

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class OutSndFileFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_nb_output_ports;
    
  private:
    boost::scoped_ptr<SndfileHandle> stream;
  public:
    OutSndFileFilter(const std::string& filename);
    
    void process_impl(long size);
    
    virtual void set_nb_input_ports(int nb_ports);
  };
}
#endif
