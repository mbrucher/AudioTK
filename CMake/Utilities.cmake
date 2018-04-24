#
# CMake utilities for ATK
#

macro(stagedebug target)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(APPLE)
      add_custom_command(TARGET ${target}
        POST_BUILD
        COMMAND dsymutil $<CONFIG>/$<TARGET_FILE_NAME:${target}>
        MAIN_DEPENDENCY ${target}
        COMMENT "Staging dSYM for ${target}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM)
    endif(APPLE)
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endmacro()

MACRO(SOURCE_GROUP_BY_FOLDER target)
  SET(SOURCE_GROUP_DELIMITER "/")

  SET(last_dir "")
  SET(files "")
  FOREACH(file ${${target}_SRC} ${${target}_HEADERS})
    file(RELATIVE_PATH relative_file "${CMAKE_CURRENT_SOURCE_DIR}" ${file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    SET(last_dir "${dir}")
  ENDFOREACH(file)
  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
ENDMACRO(SOURCE_GROUP_BY_FOLDER)

macro(ATK_scan_SIMD PREFIX ARCHS)
if(ENABLE_SIMD)
  foreach(SRC ${${PREFIX}_SIMD_SRC})
simdpp_multiarch(${PREFIX}_ARCH_GEN_SRC ${SRC} ${${ARCHS}})
  endforeach()
  FILE(GLOB FULL_PATH ${${PREFIX}_SIMD_SRC})
  LIST(APPEND ${PREFIX}_SRC ${FULL_PATH})
  LIST(APPEND ${PREFIX}_HEADERS ${${PREFIX}_SIMD_HEADERS})
  SOURCE_GROUP_BY_FOLDER(${PREFIX})
  set_source_files_properties(${${PREFIX}_SIMD_SRC} PROPERTIES HEADER_FILE_ONLY TRUE)
  LIST(APPEND ${PREFIX}_SRC ${${PREFIX}_ARCH_GEN_SRC})
else(ENABLE_SIMD)
  SOURCE_GROUP_BY_FOLDER(${PREFIX})
endif(ENABLE_SIMD)
endmacro()

function(ATK_add_library PREFIX)

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

ATK_scan_SIMD(${PREFIX} COMPILABLE_ARCHS)

if(ENABLE_STATIC_LIBRARIES)
  add_library(${${PREFIX}_NAME}_static
    STATIC
      ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
  )

  set_target_properties (${${PREFIX}_NAME}_static PROPERTIES
    FOLDER C++/static
  )

  INSTALL(TARGETS ${${PREFIX}_NAME}_static
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/ COMPONENT libraries
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT libraries
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT libraries
  )
endif(ENABLE_STATIC_LIBRARIES)

if(ENABLE_SHARED_LIBRARIES)
  add_definitions(-DBUILD_${PREFIX})
  add_definitions(-DATK_SHARED)

  add_library(${${PREFIX}_NAME}
    SHARED
    ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE} ${${PREFIX}_ARCH_GEN_SRC}
  )

  set_target_properties (${${PREFIX}_NAME} PROPERTIES
    FOLDER C++/shared
  )

  target_link_libraries(${${PREFIX}_NAME} ${${PREFIX}_LIBRARIES})

  stagedebug(${${PREFIX}_NAME})

  INSTALL(TARGETS ${${PREFIX}_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/ COMPONENT libraries
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT libraries
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT libraries
  )

endif(ENABLE_SHARED_LIBRARIES)

INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK/${${PREFIX}_FOLDER}
    FILES_MATCHING PATTERN *.h
)

endfunction()

function(ATK_add_executable PREFIX)

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

ATK_scan_SIMD(${PREFIX} RUNNABLE_ARCHS)

add_executable(${${PREFIX}_NAME}
  ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
)

if(${PREFIX}_FOLDER_PROJECT)
  set_target_properties (${${PREFIX}_NAME} PROPERTIES
    FOLDER ${${PREFIX}_FOLDER_PROJECT}
  )
endif(${PREFIX}_FOLDER_PROJECT)

target_link_libraries(${${PREFIX}_NAME} ${${PREFIX}_LIBRARIES})

endfunction()

function(ATK_add_test PREFIX)

if(NOT ${PREFIX}_TESTNAME)
  message(ERROR "No test name set for ${PREFIX}")
endif(NOT ${PREFIX}_TESTNAME)

SET(${PREFIX}_FOLDER_PROJECT Tests)

ATK_add_executable(${PREFIX})
add_test(${${PREFIX}_TESTNAME} ${${PREFIX}_NAME} --log_level=message)

endfunction()

function(ATK_add_python_module PREFIX)

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

SOURCE_GROUP_BY_FOLDER(${PREFIX})

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS} ${${PREFIX}_INCLUDE})

pybind11_add_module(${${PREFIX}_NAME} MODULE ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE})
target_link_libraries(${${PREFIX}_NAME} PRIVATE ${${PREFIX}_LIBRARIES})

SET(ATK_PYTHON_NAME "${${PREFIX}_NAME}")

configure_file (
  "${CMAKE_SOURCE_DIR}/Python/ATK/__init__.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/__init__.py" @ONLY
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)
INSTALL(TARGETS ${${PREFIX}_NAME}
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)

set_target_properties (${${PREFIX}_NAME} PROPERTIES
  FOLDER Python
)

endfunction()

INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/CMake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share
  FILES_MATCHING PATTERN "*.cmake"
)

if(ENABLE_SIMD)
  INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/3rdParty/gsl/include/gsl ${PROJECT_SOURCE_DIR}/3rdParty/eigen/Eigen ${PROJECT_SOURCE_DIR}/3rdParty/libsimdpp/simdpp
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  )
endif(ENABLE_SIMD)

include(CheckCXXCompilerFlag)

if(CMAKE_CXX_COMPILER_ID MATCHES "Apple")
  include(apple-clang)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  include(clang)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  include(gcc)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  if(MSVC)
    include(intel-msvc)
  else()
    include(intel-gcc)
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  include(msvc)
else()
  message(FATAL_ERROR "Compiler '${CMAKE_CXX_COMPILER_ID}' not recognized")
endif()
