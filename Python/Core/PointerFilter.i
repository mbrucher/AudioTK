
namespace ATK
{
template<class DataType>
class InPointerFilter
{
  
};
}



%apply (int* ARGOUT_ARRAY1, int DIM1) {(int* rangevec, int n)}


%rename(Int32InPointerFilter) ATK::InPointerFilter<std::int32_t>;
