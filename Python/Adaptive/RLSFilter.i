
%{
#include <ATK/Adaptive/RLSFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class RLSFilter: public BaseFilter
  {
  public:
    RLSFilter(std::size_t size);
    ~RLSFilter();
    
    /// Sets the memory of the RLS algorithm
    void set_memory(DataType memory);
    /// Retrieves the memory
    DataType get_memory() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;  };
}

%template(FloatRLSFilter) ATK::RLSFilter<float>;
%template(DoubleRLSFilter) ATK::RLSFilter<double>;
