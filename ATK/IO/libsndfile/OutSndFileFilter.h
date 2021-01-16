/**
 * \file OutSndFileFilter.h
 */

#ifndef ATK_IO_OUTSNDFILEFILTER_H
#define ATK_IO_OUTSNDFILEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/IO/config.h>

#include <memory>
#include <string>

class SndfileHandle;

namespace ATK
{
  /// A sink filter for sound files supported by lbsnd
  template<typename DataType_>
  class ATK_IO_EXPORT OutSndFileFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_nb_input_ports;
    
  private:
    std::unique_ptr<SndfileHandle> stream;
    std::string filename;
  protected:
    void process_impl(gsl::index size) const final;
    void setup() final;
    
  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the output file
     * @param ports is the number of output channels
     */
    OutSndFileFilter(const std::string& filename, int ports);
    /// Destructor
    ~OutSndFileFilter() override;
  };
}
#endif
