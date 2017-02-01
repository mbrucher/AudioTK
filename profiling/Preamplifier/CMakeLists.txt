
FILE(GLOB_RECURSE
    ATK_PREAMPLIFIER_PROFILE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_PREAMPLIFIER_PROFILE_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ATKPreamplifier_profile ${ATK_PREAMPLIFIER_PROFILE_SRC} ${ATK_PREAMPLIFIER_PROFILE_HEADERS})
target_link_libraries (ATKPreamplifier_profile ATKPreamplifier ATKTools ATKMock ATKCore)

set_target_properties (ATKPreamplifier_profile PROPERTIES
    FOLDER Profling
)
