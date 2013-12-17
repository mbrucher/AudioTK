/**
 * \file TriangleCheckerFilter.h
 */

#ifndef TESTS_CORE_MOCK_TRIANGLECHECKERFILTER_H
#define TESTS_CORE_MOCK_TRIANGLECHECKERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  class TriangleCheckerFilter : public TypedBaseFilter<std::int64_t>
  {
  public:
    TriangleCheckerFilter();
    virtual ~TriangleCheckerFilter();
    
  protected:
    virtual void process_impl(int size);
    
    int state;
    bool ascending;
  };
}

#endif