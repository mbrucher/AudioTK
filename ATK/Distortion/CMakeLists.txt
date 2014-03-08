
FILE(GLOB_RECURSE
    ATK_DISTORTION_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    ATK_DISTORTION_HEADERS
    *.h
)

include_directories(${PROJECT_SOURCE_DIR})
add_library(ATKDistortion
    SHARED
    ${ATK_DISTORTION_SRC} ${ATK_DISTORTION_HEADERS}
)
target_link_libraries(ATKDistortion ATKCore)

