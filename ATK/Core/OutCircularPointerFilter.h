/**
 * \file OutCircularPointerFilter.h
 */

#ifndef ATK_CORE_OUTCIRCULARPOINTERFILTER_H
#define ATK_CORE_OUTCIRCULARPOINTERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

#include <array>

namespace ATK
{
  /// Filter allowing to output data in a circular array
  template<typename DataType_>
  class ATK_CORE_EXPORT OutCircularPointerFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    static const unsigned int slice_size = 1024;
    static const unsigned int nb_slices = 66;
    static const unsigned int out_slice_size = (nb_slices - 2) * slice_size;

  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using SliceBuffer = std::array<DataType_, out_slice_size>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    
  public:
    using Parent::set_input_sampling_rate;

    /**
     * @brief Create a circular filter for the end of a pipeline
     */
    OutCircularPointerFilter();
    /// Destructor
    ~OutCircularPointerFilter() override = default;
    
    void full_setup() final;

    /// Retrieves a slice of the processed data, setting process to true if it's a new one
    auto get_last_slice(bool& process) -> const SliceBuffer&;
    
  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    void process_impl(gsl::index size) const final;
    /// Output array
    mutable std::array<DataType, nb_slices* slice_size> array{};
    SliceBuffer last_slice{};

    /// Current offset in the array
    mutable gsl::index offset{0};
    mutable gsl::index current_slice{0};
    gsl::index last_checked_out_buffer = -1;
    
  };
}

#endif
