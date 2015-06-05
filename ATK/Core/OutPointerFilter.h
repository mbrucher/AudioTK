/**
 * \file OutPointerFilter.h
 */

#ifndef ATK_CORE_OUTPOINTERFILTER_H
#define ATK_CORE_OUTPOINTERFILTER_H

#include "TypedBaseFilter.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_CORE_EXPORT OutPointerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    using Parent::set_input_sampling_rate;
    
  public:
    /**
     * @param array is the pointer to the data that will be reused during all the processing
     * @param size in the size of the data for one channel
     * @param channels is the number of total channels
     * @param interleaved indicates if the data is interleaved (Wav/Fortran order) or not (C order). If interleaved, size and channels switch position.
     */
    OutPointerFilter(DataType* array, int channels, std::int64_t size, bool interleaved);
    virtual ~OutPointerFilter();
    
    /**
     * Resets the pointer and the internal offset
     * @param array is the pointer to the new array
     * @param size is the allocated size of the array
     */
    void set_pointer(DataType* array, std::int64_t size);

  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(std::int64_t size) const override final;
    mutable std::int64_t offset;
    DataType* array;
    std::int64_t mysize;
    int channels;
    bool interleaved;
  };
}

#endif
