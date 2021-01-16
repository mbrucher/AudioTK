/**
 * \file FFTCheckerFilter.h
 */

#ifndef ATK_MOCK_FFTCHECKERFILTER_H
#define ATK_MOCK_FFTCHECKERFILTER_H

#include <ATK/Mock/config.h>
#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Utility/FFT.h>

namespace ATK
{
  /// Checks the input signal has a specific spectrum template
  template<class DataType_>
  class ATK_MOCK_EXPORT FFTCheckerFilter final: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    
    /// Constructor
    FFTCheckerFilter();
    /// Destructor
    ~FFTCheckerFilter() override;
    
    /// Sets the template we require
    void set_checks(const std::vector<std::pair<int, DataType> >& frequency_checks);
    
  protected:
    void process_impl(gsl::index size) const final;
    void setup() final;

  private:
    std::vector<std::pair<int, DataType> > frequency_checks;
    std::unique_ptr<FFT<DataType> > FFTimpl = std::make_unique<FFT<DataType_>>();
  };
}

#endif
