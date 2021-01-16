/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include <ATK/Core/BaseFilter.h>
#include <ATK/Core/TypeTraits.h>

#include <boost/align/aligned_allocator.hpp>

#include <gsl/gsl>

#include <memory>
#include <vector>

namespace ATK
{
  const gsl::index ALIGNMENT = 32;

  /// Interface for output filters
  template<typename DataType>
  class ATK_CORE_EXPORT OutputArrayInterface
  {
  public:
    virtual ~OutputArrayInterface() = default;

    /**
     * @brief Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    virtual DataType* get_output_array(gsl::index port) const = 0;
    /**
     * Returns the size of the output arrays (usually the last size processed)
     */
    virtual gsl::index get_output_array_size() const = 0;
  };

  /// Base class for typed filters, contains arrays
  template<typename DataType_, typename DataType__ = DataType_>
  class ATK_CORE_EXPORT TypedBaseFilter : public BaseFilter, public OutputArrayInterface<DataType__>
  {
  protected:
    /// Simplify parent calls
    using Parent = BaseFilter;
  public:
    /// To be used by inherited APIs
    using DataType = DataType_;
    /// To be used by inherited APIs
    using DataTypeInput = DataType_;
    /// To be used by inherited APIs
    using DataTypeOutput = DataType__;
    /// To be used for filters that require aligned data
    using AlignedVector = std::vector<DataTypeInput, boost::alignment::aligned_allocator<DataTypeInput, ALIGNMENT> >;
    /// To be used for filters that require aligned data for output data
    using AlignedOutVector = std::vector<DataTypeOutput, boost::alignment::aligned_allocator<DataTypeOutput, ALIGNMENT> >;
    /// To be used for filters that required aligned data for parameters (like EQ)
    using AlignedScalarVector = std::vector<typename TypeTraits<DataType>::Scalar, boost::alignment::aligned_allocator<typename TypeTraits<DataType>::Scalar, ALIGNMENT> >;

    /// Base constructor for filters with actual data
    TypedBaseFilter(gsl::index nb_input_ports, gsl::index nb_output_ports);
    /// Move constructor
    TypedBaseFilter(TypedBaseFilter&& other);
    /// Destructor
    ~TypedBaseFilter() override = default;

    TypedBaseFilter(const TypedBaseFilter&) = delete;
    TypedBaseFilter& operator=(const TypedBaseFilter&) = delete;

    /**
     * @brief Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    DataType__* get_output_array(gsl::index port) const final;
    gsl::index get_output_array_size() const final;

    void set_nb_input_ports(gsl::index nb_ports) override;
    void set_nb_output_ports(gsl::index nb_ports) override;

    void full_setup() override;

    /// Connects this filter input to another's output
    void set_input_port(gsl::index input_port, gsl::not_null<BaseFilter*> filter, gsl::index output_port) final;
    void set_input_port(gsl::index input_port, BaseFilter& filter, gsl::index output_port) final;

  private:
    int get_type() const override;
  protected:
    /// This implementation does nothing
    void process_impl(gsl::index size) const override;
    /// Prepares the filter by retrieving the inputs arrays
    void prepare_process(gsl::index size) final;
    /// Prepares the filter by resizing the outputs arrays
    void prepare_outputs(gsl::index size) final;

    /// Used to convert other filter outputs to DataType*
    void convert_inputs(gsl::index size);

    /// Input arrays with the input delay, owned here
    std::vector<AlignedVector> converted_inputs_delay;
    /// Input arrays, starting from t=0 (without input delay)
    std::vector<DataTypeInput*> converted_inputs;
    /// Current size of the input arrays, without delay
    std::vector<gsl::index> converted_inputs_size;
    /// Current input delay
    std::vector<gsl::index> converted_in_delays;
    /// Pointer to the output interface of the connected filters
    std::vector<OutputArrayInterface<DataType_>*> direct_filters;

    /// Output arrays with the output delay, owned here
    std::vector<AlignedOutVector> outputs_delay;
    /// Output arrays, starting from t=0 (without output delay)
    std::vector<DataTypeOutput*> outputs;
    /// Current size of the output arrays, without delay
    std::vector<gsl::index> outputs_size;
    /// Current output delay
    std::vector<gsl::index> out_delays;

    /// A vector containing the default values for the input arrays
    AlignedVector default_input;
    /// A vector containing the default values for the output arrays
    AlignedOutVector default_output;
  };
}

#endif
