/**
 * \file InSndFileFilter.h
 */

#ifndef ATK_IO_INSNDFILEFILTER_H
#define ATK_IO_INSNDFILEFILTER_H

#include <string>

#include <boost/scoped_ptr.hpp>

#include <ATK/Core/TypedBaseFilter.h>

class SndfileHandle;

namespace ATK
{
  template<typename DataType_>
  class InSndFileFilter: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    using Parent::set_output_sampling_rate;
    using Parent::set_nb_output_ports;
    
  private:
    boost::scoped_ptr<SndfileHandle> stream;
  public:
    InSndFileFilter(const std::string& filename);
    ~InSndFileFilter();
    
    void process_impl(std::int64_t size);
  };
}
#endif
