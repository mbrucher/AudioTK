/**
 * \file CachedCosinusGeneratorFilter.h
 */

#ifndef ATK_TOOLS_CACHEDCOSINUSGENERATORFILTER_H
#define ATK_TOOLS_CACHEDCOSINUSGENERATORFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Generates a cosinus signal from a cache
  template<typename DataType_>
  class ATK_TOOLS_EXPORT CachedCosinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    /*!
     * @brief Constructor
     * @param periods is the number of periods per second
     * @param seconds is the number of seconds to cache
     */
    CachedCosinusGeneratorFilter(int periods, int seconds = 1);
    /// Destructor
    ~CachedCosinusGeneratorFilter();

    /*!
    * @brief Updates the cache with new values
    * @param periods is the number of periods per second
    * @param seconds is the number of seconds to cache
    */
    void set_frequency(int periods, int seconds = 1);
    /// Retrieves the current parameters
    std::pair<int, int> get_frequency() const;

    /// Sets the output volume, doesn't update the cache
    void set_volume(DataType_ volume);
    /// Gets the output volume
    DataType_ get_volume() const;

    /// Sets the offset of the generated signal, doesn't update the cache
    void set_offset(DataType_ offset);
    /// Gets the offset
    DataType_ get_offset() const;

  protected:
    virtual void process_impl(int64_t size) const override final;
    virtual void setup() override final;
    
  private:
    mutable int64_t indice;
    int periods;
    int seconds;
    DataType_ volume;
    DataType_ offset;
    std::vector<DataType_> cache;
  };
}

#endif
