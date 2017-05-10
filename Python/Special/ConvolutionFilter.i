
%{
#include <ATK/Special/ConvolutionFilter.h>
%}

namespace ATK
{
  template<typename DataType>
  class ConvolutionFilter : public BaseFilter
  {
  public:
    ConvolutionFilter();
    ~ConvolutionFilter();

    void set_impulse(const std::vector<DataType>& impulse);
    void set_split_size(unsigned int split_size);
  };
}

%template(FloatConvolutionFilter) ATK::ConvolutionFilter<float>;
%template(DoubleConvolutionFilter) ATK::ConvolutionFilter<double>;
