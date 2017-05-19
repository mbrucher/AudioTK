/**
 * \file OutCircularPointerFilter.h
 */

#ifndef ATK_CORE_OUTCIRCULARPOINTERFILTER_H
#define ATK_CORE_OUTCIRCULARPOINTERFILTER_H

#include <array>

#include "TypedBaseFilter.h"

namespace ATK
{
  /// Filter allowing to output data in a circular array
  template<typename DataType_>
  class ATK_CORE_EXPORT OutCircularPointerFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    static const unsigned int slice_size = 1024;
    static const unsigned int nb_slices = 32;
    static const unsigned int out_slice_size = (nb_slices - 2) * slice_size;

    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    typedef std::array<DataType_, out_slice_size> SliceBuffer;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_input_sampling_rate;
    
  public:
    /**
     * @brief Create a circular filter for the end of a pipeline
     */
    OutCircularPointerFilter();
    /// Destructor
    virtual ~OutCircularPointerFilter();
    
    void full_setup() override;

    /// Retrieves a slice of the processed data, setting process to true if it's a new one
    const SliceBuffer& get_last_slice(bool& process);
    
  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(std::size_t size) const override final;
    /// Output array
    mutable std::array<DataType, nb_slices * slice_size> array;
    SliceBuffer last_slice;

    /// Current offset in the array
    mutable std::size_t offset;
    mutable std::size_t current_slice;
    std::size_t last_checked_out_buffer;
    
  };
}

#endif
