/**
 * \file TriangleCheckerFilter.h
 */

#ifndef ATK_MOCK_TRIANGLECHECKERFILTER_H
#define ATK_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  class TriangleCheckerFilter : public TypedBaseFilter<std::int64_t>
  {
  public:
    TriangleCheckerFilter();
    virtual ~TriangleCheckerFilter();
    
    void set_amplitude(std::int64_t amplitude);
    void set_frequency(int frequency);

  protected:
    virtual void process_impl(int size);
    
    float state;
    bool ascending;
    std::int64_t amplitude;
    int frequency;
  };
}

#endif