/**
 * \file OutSndFileFilter.h
 */

#ifndef ATK_IO_OUTSNDFILEFILTER_H
#define ATK_IO_OUTSNDFILEFILTER_H

#include <string>

#include <boost/scoped_ptr.hpp>

#include <ATK/Core/TypedBaseFilter.h>

class SndfileHandle;

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
    using Parent::set_nb_input_ports;
    
  private:
    boost::scoped_ptr<SndfileHandle> stream;
    std::string filename;
  public:
    OutSndFileFilter(const std::string& filename, int ports);
    ~OutSndFileFilter();
    
    void process_impl(std::int64_t size);
    void setup();
  };
}
#endif
