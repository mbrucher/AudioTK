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
  template<typename DataType_>
  class TypedBaseFilter : public BaseFilter
  {
  protected:
    typedef DataType_ DataType;
    typedef BaseFilter Parent;

  public:
    TypedBaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ~TypedBaseFilter();
    
    /**
     * Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    DataType* get_output_array(int port);
    
    virtual void set_nb_input_ports(int nb_ports);
    virtual void set_nb_output_ports(int nb_ports);
    virtual int get_type() const;

  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(long size);
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(long size);
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(long size);
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(long size);
    
    std::vector<boost::scoped_array<DataType> > converted_inputs;
    std::vector<int> converted_inputs_size;
    std::vector<boost::scoped_array<DataType> > outputs;
    std::vector<int> outputs_size;
  };
}

#endif
