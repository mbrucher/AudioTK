/**
 * \file TypedBaseFilter.h
 */

#ifndef ATK_CORE_TYPEDBASEFILTER_H
#define ATK_CORE_TYPEDBASEFILTER_H

#include "BaseFilter.h"

#include <memory>
#include <vector>

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

    virtual void full_setup() override;

  protected:
    virtual int get_type() const override;
    /// This implementation retrieves inputs from other filters and converts it accordingly
    virtual void process_impl(int64_t size) const override;
    /// Prepares the filter by retrieving the inputs arrays
    virtual void prepare_process(int64_t size) override final;
    /// Prepares the filter by resizing the outputs arrays
    virtual void prepare_outputs(int64_t size) override final;
    
    /// Used to convert other filter outputs to DataType*
    void convert_inputs(int64_t size);

    std::vector<std::unique_ptr<DataType[]> > converted_inputs_delay;
    std::vector<DataType *> converted_inputs;
    std::vector<int64_t> converted_inputs_size;

    std::vector<std::unique_ptr<DataType[]> > outputs_delay;
    std::vector<DataType *> outputs;
    std::vector<int64_t> outputs_size;
  };
}

#endif
