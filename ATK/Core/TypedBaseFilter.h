/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include "BaseFilter.h"

#include <memory>
#include <vector>

#include <boost/align/aligned_allocator.hpp>

namespace ATK
{
  /// Base class for typed filters, contains arrays
  template<typename DataType_>
  class ATK_CORE_EXPORT TypedBaseFilter : public BaseFilter
  {
  protected:
    /// Simplify parent calls
    typedef BaseFilter Parent;
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    /// To be used for filters that require alignment (like EQs)
    typedef std::vector<DataType, boost::alignment::aligned_allocator<DataType, 32> > AlignedVector;

    /// Base constructor for filters with actual data
    TypedBaseFilter(unsigned int nb_input_ports, unsigned int nb_output_ports);
    /// Move constructor
    TypedBaseFilter(TypedBaseFilter&& other);
    /// Destructor
    virtual ~TypedBaseFilter();
    
    TypedBaseFilter(const TypedBaseFilter&) = delete;
    TypedBaseFilter& operator=(const TypedBaseFilter&) = delete;

    /**
     * @brief Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    DataType* get_output_array(std::size_t port);

    virtual void set_nb_input_ports(std::size_t nb_ports) override;
    virtual void set_nb_output_ports(std::size_t nb_ports) override;

    virtual void full_setup() override;

    virtual void set_input_port(unsigned int input_port, BaseFilter* filter, unsigned int output_port) override final;
    
  protected:

    virtual int get_type() const override;
    /// This implementation does nothing
    virtual void process_impl(std::size_t size) const override;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(std::size_t size) override final;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(std::size_t size) override final;
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(std::size_t size);

    /// Input arrays, starting from t=0 (without input delay)
    std::vector<DataType *> converted_inputs;

    /// Output arrays, starting from t=0 (without output delay)
    std::vector<DataType *> outputs;

    /// A vector containing the default values for the input arrays
    std::vector<DataType> default_input;
    /// A vector containing the default values for the output arrays
    std::vector<DataType> default_output;
private:
  typedef std::pair<std::unique_ptr<DataType[]>, std::size_t> DataSize;
  typedef std::vector<DataSize> CustomDataSize;
  /// Input arrays with the input delay, owned here
  CustomDataSize converted_inputs_delay;
  /// Output arrays with the output delay, owned here
  CustomDataSize outputs_delay;
#ifndef NDEBUG
  std::vector<std::size_t> input_size;
  std::vector<std::size_t> output_size;
#endif
  };
}

#endif
