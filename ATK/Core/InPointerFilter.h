/**
 * \file InPointerFilter.h
 */

#ifndef ATK_CORE_INPOINTERFILTER_H
#define ATK_CORE_INPOINTERFILTER_H

#include "TypedBaseFilter.h"

namespace ATK
{
  template<typename DataType_>
  class ATK_CORE_EXPORT InPointerFilter : public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    using Parent::set_output_sampling_rate;
    using Parent::set_nb_output_ports;
    
  public:
    /**
     * @param array is the pointer to the data that will be reused during all the processing
     * @param size in the size of the data for one channel
     * @param channels is the number of total channels
     * @param interleaved indicates if the data is interleaved (Wav/Fortran order) or not (C order)
     */
    InPointerFilter(const DataType* array, int channels, std::int64_t size, bool interleaved);
    virtual ~InPointerFilter();
    
    /**
     * Resets the pointer and the internal offset
     * @param array is the pointer to the new array
     * @param size is the allocated size of the array
     */
    void set_pointer(const DataType* array, std::int64_t size);
    
  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(std::int64_t size);
    std::int64_t offset;
    const DataType* array;
    std::int64_t mysize;
    int channels;
    bool interleaved;
  };
}

#endif
