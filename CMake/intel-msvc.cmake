SET(NATVIS_FILE ${PROJECT_SOURCE_DIR}/atk.natvis)
SET_SOURCE_FILES_PROPERTIES(${NATVIS_FILE} LANGUAGE natvis)

set(MSVC_RUNTIME "Dynamic" CACHE STRING "Set up MSVC Runtime (Dynamic/Static)")

if("${MSVC_RUNTIME}" STREQUAL "Static")
  set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
endif("${MSVC_RUNTIME}" STREQUAL "Static")

CHECK_CXX_COMPILER_FLAG("/Qstd=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qstd=c++14")
else(COMPILER_SUPPORTS_CXX14)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /QC++14.")
  CHECK_CXX_COMPILER_FLAG("/Qstd=c++11" COMPILER_SUPPORTS_CXX11)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qstd=c++11")
  else(COMPILER_SUPPORTS_CXX11)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /QC++11.")
  endif(COMPILER_SUPPORTS_CXX11)
endif(COMPILER_SUPPORTS_CXX14)

CHECK_CXX_COMPILER_FLAG("/fp:fast" COMPILER_SUPPORTS_fastmath)
if(COMPILER_SUPPORTS_fastmath)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
else(COMPILER_SUPPORTS_fastmath)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /fp:fast.")
endif(COMPILER_SUPPORTS_fastmath)

if(ENABLE_PROFILE_INFO)
  CHECK_CXX_COMPILER_FLAG("/Qopt-report:2 /Qopt-report-phase=vec" COMPILER_SUPPORTS_vectorreport1)
  if(COMPILER_SUPPORTS_vectorreport1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qopt-report:2 /Qopt-report-phase=vec")
  else(COMPILER_SUPPORTS_vectorreport1)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qopt-report:2 /Qopt-report-phase=vec.")
  endif(COMPILER_SUPPORTS_vectorreport1)
endif(ENABLE_PROFILE_INFO)

CHECK_CXX_COMPILER_FLAG("/Qrestrict" COMPILER_SUPPORTS_restrict)
if(COMPILER_SUPPORTS_restrict)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qrestrict")
else(COMPILER_SUPPORTS_restrict)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qrestrict.")
endif(COMPILER_SUPPORTS_restrict)

CHECK_CXX_COMPILER_FLAG("/Qftz" COMPILER_SUPPORTS_ftz)
if(COMPILER_SUPPORTS_ftz)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qftz")
else(COMPILER_SUPPORTS_ftz)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qftz.")
endif(COMPILER_SUPPORTS_ftz)

CHECK_CXX_COMPILER_FLAG("/QxAVX /QaxCORE-AVX2" COMPILER_SUPPORTS_AVX)
if(COMPILER_SUPPORTS_AVX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /QxAVX /QaxCORE-AVX2")
else(COMPILER_SUPPORTS_AVX)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /QxAVX /QaxCORE-AVX2.")
endif(COMPILER_SUPPORTS_AVX)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
  add_definitions(-DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
