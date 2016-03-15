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
  /// A sink filter for sound files supported by lbsnd
  template<typename DataType_>
  class OutSndFileFilter: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_nb_input_ports;
    
  private:
    boost::scoped_ptr<SndfileHandle> stream;
    std::string filename;
  protected:
    void process_impl(int64_t size) const override final;
    void setup() override final;
    
  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the output file
     * @param ports is the number of output channels
     */
    OutSndFileFilter(const std::string& filename, int ports);
    /// Destructor
    ~OutSndFileFilter();
  };
}
#endif
