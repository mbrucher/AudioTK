/**
 * \file Adaptive.cpp
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Adaptive/BlockLMSFilter.h>
#include <ATK/Adaptive/LMSFilter.h>
#include <ATK/Adaptive/RLSFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename DataType, typename T>
  void populate_BlockLMSFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<BlockLMSFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("size"))
    .def_property("size", &BlockLMSFilter<DataType>::get_size, &BlockLMSFilter<DataType>::set_size)
    .def_property("block_size", &BlockLMSFilter<DataType>::get_block_size, &BlockLMSFilter<DataType>::set_block_size)
    .def_property("memory", &BlockLMSFilter<DataType>::get_memory, &BlockLMSFilter<DataType>::set_memory)
    .def_property("mu", &BlockLMSFilter<DataType>::get_mu, &BlockLMSFilter<DataType>::set_mu)
    .def_property("learning", &BlockLMSFilter<DataType>::get_learning, &BlockLMSFilter<DataType>::set_learning)
    .def_property("w", [](const BlockLMSFilter<DataType>& instance){
      return py::array_t<std::complex<double>>(instance.get_size() * 2, instance.get_w());
    },[](BlockLMSFilter<DataType>& instance, const py::array_t<std::complex<double>>& array){
      if(array.ndim() != 1 || array.shape()[0] != instance.get_size() * 2)
      {
        throw std::length_error("Wrong size for w, it must be complex with the size equal to twice the size of the filter");
      }
      instance.set_w(array.data());
    });
  }

  template<typename DataType, typename T>
  void populate_LMSFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<LMSFilter<DataType>> filter(m, type, parent);
    filter.def(py::init<gsl::index>(), py::arg("size"))
    .def_property("size", &LMSFilter<DataType>::get_size, &LMSFilter<DataType>::set_size)
    .def_property("memory", &LMSFilter<DataType>::get_memory, &LMSFilter<DataType>::set_memory)
    .def_property("mu", &LMSFilter<DataType>::get_mu, &LMSFilter<DataType>::set_mu)
    .def_property("mode", &LMSFilter<DataType>::get_mode, &LMSFilter<DataType>::set_mode)
    .def_property("learning", &LMSFilter<DataType>::get_learning, &LMSFilter<DataType>::set_learning)
    .def_property("w", [](const LMSFilter<DataType>& instance){
      return py::array_t<DataType>(instance.get_size(), instance.get_w());
    }, [](LMSFilter<DataType>& instance, const py::array_t<DataType>& array){
      if(array.ndim() != 1 || array.shape()[0] != instance.get_size())
      {
        throw std::length_error("Wrong size for w, must have the size of the filter");
      }
      instance.set_w(array.data());
    });
    
    py::enum_<typename LMSFilter<DataType>::Mode>(filter, "Mode")
    .value("NORMAL", LMSFilter<DataType>::Mode::NORMAL)
    .value("NORMALIZED", LMSFilter<DataType>::Mode::NORMALIZED)
    .value("SIGNERROR", LMSFilter<DataType>::Mode::SIGNERROR)
    .value("SIGNDATA", LMSFilter<DataType>::Mode::SIGNDATA)
    .value("SIGNSIGN", LMSFilter<DataType>::Mode::SIGNSIGN)
    .export_values();
  }

  template<typename DataType, typename T>
  void populate_RLSFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<RLSFilter<DataType>>(m, type, parent)
    .def(py::init<gsl::index>(), py::arg("size"))
    .def_property("size", &RLSFilter<DataType>::get_size, &RLSFilter<DataType>::set_size)
    .def_property("memory", &RLSFilter<DataType>::get_memory, &RLSFilter<DataType>::set_memory)
    .def_property("learning", &RLSFilter<DataType>::get_learning, &RLSFilter<DataType>::set_learning)
    .def_property("w", [](const RLSFilter<DataType>& instance){
      return py::array_t<DataType>(instance.get_size(), instance.get_w());
    },[](RLSFilter<DataType>& instance, py::array_t<DataType>& array){
      if(array.ndim() != 1 || array.shape()[0] != instance.get_size())
      {
        throw std::length_error("Wrong size for w, must have the size of the filter");
      }
      instance.set_w(array.data());
    })
    .def_property("P", [](const RLSFilter<DataType>& instance){
      return py::array_t<DataType>({instance.get_size(), instance.get_size()}, instance.get_P());
    },[](RLSFilter<DataType>& instance, const py::array_t<DataType>& array){
      if(array.ndim() != 2 || (array.shape()[0] != instance.get_size() && array.shape()[1] != instance.get_size()))
      {
        throw std::length_error("Wrong size for P, must have (size, size)");
      }
      instance.set_P(array.data());
    }
    );
  }
}

PYBIND11_MODULE(PythonAdaptive, m)
{
  m.doc() = "Audio ToolKit Adaptive module";

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");
  py::object f3 = (py::object) py::module::import("ATK.Core").attr("ComplexFloatTypedBaseFilter");
  py::object f4 = (py::object) py::module::import("ATK.Core").attr("ComplexDoubleTypedBaseFilter");
  
  populate_BlockLMSFilter<double>(m, "DoubleBlockLMSFilter", f2);
  populate_BlockLMSFilter<std::complex<double>>(m, "ComplexDoubleBlockLMSFilter", f2);
  
  populate_LMSFilter<float>(m, "FloatLMSFilter", f1);
  populate_LMSFilter<double>(m, "DoubleLMSFilter", f2);
  populate_LMSFilter<std::complex<float>>(m, "ComplexFloatLMSFilter", f3);
  populate_LMSFilter<std::complex<double>>(m, "ComplexDoubleLMSFilter", f4);

  populate_RLSFilter<float>(m, "FloatRLSFilter", f1);
  populate_RLSFilter<double>(m, "DoubleRLSFilter", f2);
  populate_RLSFilter<std::complex<float>>(m, "ComplexFloatRLSFilter", f3);
  populate_RLSFilter<std::complex<double>>(m, "ComplexDoubleRLSFilter", f4);
}
