/**
 * \file TriangleGeneratorFilter.h
 */

#ifndef TESTS_CORE_MOCK_TRIANGLEGENERATORFILTER_H
#define TESTS_CORE_MOCK_TRIANGLEGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  class TriangleGeneratorFilter : public TypedBaseFilter<std::int64_t>
  {
  public:
    TriangleGeneratorFilter();
    virtual ~TriangleGeneratorFilter();
    
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
