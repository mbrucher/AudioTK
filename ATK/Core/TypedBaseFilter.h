/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include "BaseFilter.h"

#include <vector>

#include <boost/scoped_array.hpp>

#define UGLYHACK
#ifdef UGLYHACK
#include <boost/shared_array.hpp>
#define scoped_array shared_array
#endif

namespace ATK
{
  template<typename DataType_>
  class ATK_CORE_EXPORT TypedBaseFilter : public BaseFilter
  {
  protected:
    typedef BaseFilter Parent;

  public:
    typedef DataType_ DataType;

    TypedBaseFilter(int nb_input_ports, int nb_output_ports);
    virtual ~TypedBaseFilter();
    
    /**
     * Returns an array with the processed output
     * @param port is the port that the next plugin listens to
     */
    DataType* get_output_array(int port);

    virtual void set_nb_input_ports(int nb_ports) override;
    virtual void set_nb_output_ports(int nb_ports) override;

  protected:
    virtual int get_type() const;
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(std::int64_t size) override;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(std::int64_t size) override;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(std::int64_t size) override;
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(std::int64_t size);
    void full_setup();

    std::vector<boost::scoped_array<DataType> > converted_inputs_delay;
    std::vector<DataType *> converted_inputs;
    std::vector<std::int64_t> converted_inputs_size;
    std::vector<boost::scoped_array<DataType> > outputs_delay;
    std::vector<DataType *> outputs;
    std::vector<std::int64_t> outputs_size;
  };
}

#endif
