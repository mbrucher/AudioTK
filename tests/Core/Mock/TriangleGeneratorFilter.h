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
    
  protected:
    virtual void process_impl(int size);

    int state;
    bool ascending;
  };
}

#endif
