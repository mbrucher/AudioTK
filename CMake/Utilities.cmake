#
# CMake utilities for ATK
#

function(ATK_add_library PREFIX)

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

if(ENABLE_SIMD)
  foreach(SRC ${${PREFIX}_SIMD_SRC})
    simdpp_multiarch(${PREFIX}_ARCH_GEN_SRC ${SRC} ${COMPILABLE_ARCHS})
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

INSTALL(FILES ${${PREFIX}_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK/${${PREFIX}_FOLDER}
)

endfunction()

function(ATK_add_executable PREFIX)

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

SOURCE_GROUP_BY_FOLDER(${PREFIX})

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

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

INSTALL(FILES __init__.py
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)
INSTALL(TARGETS ${${PREFIX}_NAME}
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)

set_target_properties (${${PREFIX}_NAME} PROPERTIES
  FOLDER Python
)

endfunction()
