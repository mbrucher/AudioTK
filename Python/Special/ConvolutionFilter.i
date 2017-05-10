
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

    void set_impulse(std::vector<DataType> impulse);
    void set_split_size(unsigned int split_size);
  };
}

%template(DoubleConvolutionFilter) ATK::ConvolutionFilter<double>;
