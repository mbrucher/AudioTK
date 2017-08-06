/**
* \file Distortion.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Distortion/DiodeClipperFilter.h>
#include <ATK/Distortion/SD1OverdriveFilter.h>
#include <ATK/Distortion/SimpleOverdriveFilter.h>
#include <ATK/Distortion/TS9OverdriveFilter.h>

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
}

PYBIND11_PLUGIN(PythonDistortion) {
  py::module m("PythonDistortion", "Audio ToolKit Distortion module");

  py::object f1 = (py::object) py::module::import("ATK.Core").attr("FloatTypedBaseFilter");
  py::object f2 = (py::object) py::module::import("ATK.Core").attr("DoubleTypedBaseFilter");

  populate_Filter<DiodeClipperFilter<float>>(m, "FloatDiodeClipperFilter", f1);
  populate_Filter<DiodeClipperFilter<double>>(m, "DoubleDiodeClipperFilter", f2);

  populate_Filter<SimpleOverdriveFilter<float>>(m, "FloatSimpleOverdriveFilter", f1);
  populate_Filter<SimpleOverdriveFilter<double>>(m, "DoubleSimpleOverdriveFilter", f2);

  populate_DriveFilter<SD1OverdriveFilter<float>>(m, "FloatSD1OverdriveFilter", f1);
  populate_DriveFilter<SD1OverdriveFilter<double>>(m, "DoubleSD1OverdriveFilter", f2);

  populate_DriveFilter<TS9OverdriveFilter<float>>(m, "FloatTS9OverdriveFilter", f1);
  populate_DriveFilter<TS9OverdriveFilter<double>>(m, "DoubleTS9OverdriveFilter", f2);

  populate_Filter<TanhShaperFilter<float>>(m, "FloatTanhShaperFilter", f1);
  populate_Filter<TanhShaperFilter<double>>(m, "DoubleTanhShaperFilter", f2);

  return m.ptr();
}
