/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include "BaseFilter.h"

#include <vector>

#include <boost/scoped_array.hpp>

namespace ATK
{
  template<typename DataType>
  class TypedBaseFilter : public BaseFilter
  {
  public:
    TypedBaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ~TypedBaseFilter();
    
    /**
     * Returns an array with the processed output
     * @param port is the port
     */
    DataType* get_output_array(int port, int size);
    
  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl();
    virtual int get_type() const;
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(int size);
    
    std::vector<boost::scoped_array<DataType> > converted_inputs;
    std::vector<int> converted_inputs_size;
    std::vector<boost::scoped_array<DataType> > outputs;
    std::vector<int> outputs_size;
  };
}

#endif
