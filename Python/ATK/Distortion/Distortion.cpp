/**
* \file Distortion.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Distortion/DiodeClipperFilter.h>
#include <ATK/Distortion/SD1OverdriveFilter.h>
#include <ATK/Distortion/SimpleOverdriveFilter.h>
#include <ATK/Distortion/TS9OverdriveFilter.h>

#include <ATK/Distortion/HalfTanhShaperFilter.h>
#include <ATK/Distortion/TanhShaperFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  template<typename Filter, typename T>
  void populate_Filter(py::module& m, const char* type, T& parent)
  {
    py::class_<Filter>(m, type, parent)
    .def(py::init<>());
  }

  template<typename Filter, typename T>
  void populate_DriveFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<Filter>(m, type, parent)
      .def(py::init<>())
      .def_property("drive", &Filter::get_drive, &Filter::set_drive);
  }

  template<typename Filter, typename T>
  void populate_ShaperFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<Filter>(m, type, parent)
    .def(py::init<>())
    .def_property("coefficient", &Filter::get_coefficient, &Filter::set_coefficient);
  }
}

PYBIND11_MODULE(PythonDistortion, m) {
  m.doc() = "Audio ToolKit Distortion module";

#if ATK_ENABLE_INSTANTIATION
  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
#endif
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

#if ATK_ENABLE_INSTANTIATION
  populate_Filter<DiodeClipperFilter<float>>(m, "FloatDiodeClipperFilter", f1);
#endif
  populate_Filter<DiodeClipperFilter<double>>(m, "DoubleDiodeClipperFilter", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_Filter<SimpleOverdriveFilter<float>>(m, "FloatSimpleOverdriveFilter", f1);
#endif
  populate_Filter<SimpleOverdriveFilter<double>>(m, "DoubleSimpleOverdriveFilter", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_DriveFilter<SD1OverdriveFilter<float>>(m, "FloatSD1OverdriveFilter", f1);
#endif
  populate_DriveFilter<SD1OverdriveFilter<double>>(m, "DoubleSD1OverdriveFilter", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_DriveFilter<TS9OverdriveFilter<float>>(m, "FloatTS9OverdriveFilter", f1);
#endif
  populate_DriveFilter<TS9OverdriveFilter<double>>(m, "DoubleTS9OverdriveFilter", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_ShaperFilter<TanhShaperFilter<float>>(m, "FloatTanhShaperFilter", f1);
#endif
  populate_ShaperFilter<TanhShaperFilter<double>>(m, "DoubleTanhShaperFilter", f2);

#if ATK_ENABLE_INSTANTIATION
  populate_ShaperFilter<HalfTanhShaperFilter<float>>(m, "FloatHalfTanhShaperFilter", f1);
#endif
  populate_ShaperFilter<HalfTanhShaperFilter<double>>(m, "DoubleHalfTanhShaperFilter", f2);
}
