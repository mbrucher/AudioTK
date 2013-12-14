/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include "BaseFilter.h"

namespace ATK
{
  template<typename DataType>
  class TypedBaseFilter : public BaseFilter
  {
  public:
    TypedBaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ~TypedBaseFilter();
    
  protected:
    virtual void process_impl();
    virtual void update_impl();
  };
}

#endif
