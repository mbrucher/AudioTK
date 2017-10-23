/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/Core/TypeTraits.h>

#include <memory>
#include <vector>

#include <boost/align/aligned_allocator.hpp>

namespace ATK
{
  const std::size_t ALIGNMENT = 32;
  
  /// Interface for output filters
  template<typename DataType>
  class OutputArrayInterface
  {
  public:
    virtual ~OutputArrayInterface();
    
    /**
     * @brief Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    virtual DataType* get_output_array(std::size_t port) const = 0;
    /**
     * Returns the size of the output arrays (usually the last size processed)
     */
    virtual std::size_t get_output_array_size() const = 0;
  };
  
  /// Base class for typed filters, contains arrays
  template<typename DataType_, typename DataType__ = DataType_>
  class ATK_CORE_EXPORT TypedBaseFilter : public BaseFilter, public OutputArrayInterface<DataType__>
  {
  protected:
    /// Simplify parent calls
    typedef BaseFilter Parent;
  public:
    /// To be used by inherited APIs
    typedef DataType_ DataType;
    /// To be used by inherited APIs
    typedef DataType_ DataTypeInput;
    /// To be used by inherited APIs
    typedef DataType__ DataTypeOutput;
    /// To be used for filters that require aligned data
    typedef std::vector<DataTypeInput, boost::alignment::aligned_allocator<DataTypeInput, ALIGNMENT> > AlignedVector;
    /// To be used for filters that require aligned data for output data
    typedef std::vector<DataTypeOutput, boost::alignment::aligned_allocator<DataTypeOutput, ALIGNMENT> > AlignedOutVector;
    /// To be used for filters that required aligned data for parameters (like EQ)
    typedef std::vector<typename TypeTraits<DataType>::Scalar, boost::alignment::aligned_allocator<typename TypeTraits<DataType>::Scalar, ALIGNMENT> > AlignedScalarVector;

    /// Base constructor for filters with actual data
    TypedBaseFilter(std::size_t nb_input_ports, std::size_t nb_output_ports);
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
    DataType__* get_output_array(std::size_t port) const final;
    std::size_t get_output_array_size() const final;

    void set_nb_input_ports(std::size_t nb_ports) override;
    void set_nb_output_ports(std::size_t nb_ports) override;

    void full_setup() override;

    /// Connects this filter input to another's output
    void set_input_port(std::size_t input_port, BaseFilter* filter, std::size_t output_port) final;
    
  private:
    int get_type() const override;
  protected:
    /// This implementation does nothing
    void process_impl(std::size_t size) const override;
    /// Prepares the filter by retrieving the inputs arrays
    void prepare_process(std::size_t size) final;
    /// Prepares the filter by resizing the outputs arrays
    void prepare_outputs(std::size_t size) final;
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(std::size_t size);

    /// Input arrays with the input delay, owned here
    std::vector<std::unique_ptr<DataTypeInput[]> > converted_inputs_delay;
    /// Input arrays, starting from t=0 (without input delay)
    std::vector<DataTypeInput*> converted_inputs;
    /// Current size of the input arrays, without delay
    std::vector<std::size_t> converted_inputs_size;
    /// Pointer to the output interface of the connected filters
    std::vector<OutputArrayInterface<DataType_>*> direct_filters;

    /// Output arrays with the output delay, owned here
    std::vector<std::unique_ptr<DataTypeOutput[]> > outputs_delay;
    /// Output arrays, starting from t=0 (without output delay)
    std::vector<DataTypeOutput*> outputs;
    /// Current size of the output arrays, without delay
    std::vector<std::size_t> outputs_size;

    /// A vector containing the default values for the input arrays
    AlignedVector default_input;
    /// A vector containing the default values for the output arrays
    AlignedOutVector default_output;
  };
}

#endif
