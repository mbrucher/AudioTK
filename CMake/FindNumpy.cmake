# - Find the NumPy libraries
# This module finds if NumPy is installed, and sets the following variables
# indicating where it is.
#
# TODO: Update to provide the libraries and paths for linking npymath lib.
#
#  NUMPY_FOUND               - was NumPy found
#  NUMPY_VERSION             - the version of NumPy found as a string
#  NUMPY_VERSION_MAJOR       - the major version number of NumPy
#  NUMPY_VERSION_MINOR       - the minor version number of NumPy
#  NUMPY_VERSION_PATCH       - the patch version number of NumPy
#  NUMPY_VERSION_DECIMAL     - e.g. version 1.6.1 is 10601
#  NUMPY_INCLUDE_DIRS        - path to the NumPy include files

#============================================================================
# Copyright 2012 Continuum Analytics, Inc.
#
# MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
#============================================================================

# Finding NumPy involves calling the Python interpreter
if(NumPy_FIND_REQUIRED)
    find_package(PythonInterp REQUIRED)
else()
    find_package(PythonInterp)
endif()

if(NOT PYTHONINTERP_FOUND)
    set(NUMPY_FOUND FALSE)
    return()
endif()

if (PYTHON_EXECUTABLE)
  # Find out the include path
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
            "from __future__ import print_function\ntry: import numpy; print(numpy.get_include(), end='')\nexcept:pass\n"
            OUTPUT_VARIABLE __numpy_path)
  # And the version
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
            "from __future__ import print_function\ntry: import numpy; print(numpy.__version__, end='')\nexcept:pass\n"
    OUTPUT_VARIABLE __numpy_version)
elseif(__numpy_out)
  message(STATUS "Python executable not found.")
endif(PYTHON_EXECUTABLE)

find_path(PYTHON_NUMPY_INCLUDE_DIR numpy/arrayobject.h
  HINTS "${__numpy_path}" "${PYTHON_INCLUDE_PATH}" NO_DEFAULT_PATH)

if(PYTHON_NUMPY_INCLUDE_DIR)
  set(PYTHON_NUMPY_FOUND 1 CACHE INTERNAL "Python numpy found")
endif(PYTHON_NUMPY_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NumPy REQUIRED_VARS PYTHON_NUMPY_INCLUDE_DIR
                                        VERSION_VAR __numpy_version)

message(status ${PYTHON_NUMPY_INCLUDE_DIR})
                                        