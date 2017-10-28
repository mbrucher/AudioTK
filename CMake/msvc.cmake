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

CHECK_CXX_COMPILER_FLAG("/fp:fast" COMPILER_SUPPORTS_fastmath)
if(COMPILER_SUPPORTS_fastmath)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
else(COMPILER_SUPPORTS_fastmath)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /fp:fast.")
endif(COMPILER_SUPPORTS_fastmath)

CHECK_CXX_COMPILER_FLAG("/MP" COMPILER_SUPPORTS_MP)
if(COMPILER_SUPPORTS_MP)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else(COMPILER_SUPPORTS_MP)
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /MP.")
endif(COMPILER_SUPPORTS_MP)

if(ENABLE_PROFILE_INFO)
  CHECK_CXX_COMPILER_FLAG("/Qvec-report:2" COMPILER_SUPPORTS_vectorreport)
  if(COMPILER_SUPPORTS_vectorreport)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qvec-report:2")
  else(COMPILER_SUPPORTS_vectorreport)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support /Qvec-report:2.")
  endif(COMPILER_SUPPORTS_vectorreport)
endif(ENABLE_PROFILE_INFO)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
  add_definitions(-DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
