#
# CMake utilities for ATL
#

function(ATK_add_library PREFIX)

SOURCE_GROUP_BY_FOLDER(${PREFIX})

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

if(ENABLE_STATIC_LIBRARIES)
  add_library(${PREFIX}_static
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
    ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
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

SOURCE_GROUP_BY_FOLDER(${PREFIX})

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

add_executable(${${PREFIX}_NAME}
  ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
)

set_target_properties (${${PREFIX}_NAME} PROPERTIES
  FOLDER Profling
)

target_link_libraries(${${PREFIX}_NAME} ${${PREFIX}_LIBRARIES})

endfunction()

function(ATK_add_test PREFIX)

ATK_add_executable(${PREFIX})
add_test(${${PREFIX}_TESTNAME} ${${PREFIX}_NAME} --log_level=message)

if(${PREFIX}_FOLDER_PROJECT)
  set_target_properties (${${PREFIX}_NAME} PROPERTIES
    FOLDER ${${PREFIX}_FOLDER_PROJECT}
  )
endif(${PREFIX}_FOLDER_PROJECT)

endfunction()

function(ATK_add_python_module PREFIX)

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
