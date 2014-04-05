
FIND_PATH(ACCELERATE_FRAMEWORK_INCLUDE_DIR cblas.h /usr/include /usr/local/include
        /System/Library/Frameworks/vecLib.framework/Versions/A/Headers/ )

MARK_AS_ADVANCED(ACCELERATE_FRAMEWORK_INCLUDE_DIR)

SET( ACCELERATE_FRAMEWORK_LINK_FLAGS "-framework Accelerate" )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Accelerate DEFAULT_MSG ACCELERATE_FRAMEWORK_INCLUDE_DIR ACCELERATE_FRAMEWORK_LINK_FLAGS)

