
  CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
  if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  else(COMPILER_SUPPORTS_CXX14)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support C++14.")
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX11)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else(COMPILER_SUPPORTS_CXX11)
       message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support C++11.")
    endif(COMPILER_SUPPORTS_CXX11)
  endif(COMPILER_SUPPORTS_CXX14)

  CHECK_CXX_COMPILER_FLAG("-pthread" COMPILER_SUPPORTS_PTHREAD)
  if(COMPILER_SUPPORTS_PTHREAD)
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pthread")
  else(COMPILER_SUPPORTS_PTHREAD)
   message(STATUS "The linker ${CMAKE_CXX_COMPILER} doesn't support -pthread.")
  endif(COMPILER_SUPPORTS_PTHREAD)

  if(ENABLE_PROFILE_INFO)
    CHECK_CXX_COMPILER_FLAG("-qopt-report:2 -qopt-report-phase=vec" COMPILER_SUPPORTS_vectorreport)
    if(COMPILER_SUPPORTS_vectorreport)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopt-report:2 -opt-report-phase=vec")
    else(COMPILER_SUPPORTS_vectorreport)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -qopt-report:2 -qopt-report-phase=vec.")
    endif(COMPILER_SUPPORTS_vectorreport)
  endif(ENABLE_PROFILE_INFO)

  CHECK_CXX_COMPILER_FLAG("-restrict" COMPILER_SUPPORTS_restrict)
  if(COMPILER_SUPPORTS_restrict)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -restrict")
  else(COMPILER_SUPPORTS_restrict)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -restrict.")
  endif(COMPILER_SUPPORTS_restrict)

  CHECK_CXX_COMPILER_FLAG("-ftz" COMPILER_SUPPORTS_ftz)
  if(COMPILER_SUPPORTS_ftz)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftz")
  else(COMPILER_SUPPORTS_ftz)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -ftz.")
  endif(COMPILER_SUPPORTS_ftz)

  CHECK_CXX_COMPILER_FLAG("-fdenormal-fp-math=positive-zero" COMPILER_SUPPORTS_ftpz)
  if(COMPILER_SUPPORTS_ftpz)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdenormal-fp-math=positive-zero")
  else(COMPILER_SUPPORTS_ftpz)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -fdenormal-fp-math=positive-zero.")
  endif(COMPILER_SUPPORTS_ftpz)

  CHECK_CXX_COMPILER_FLAG("-xAVX -axCORE-AVX2" COMPILER_SUPPORTS_AVX)
  if(COMPILER_SUPPORTS_AVX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -xAVX -axCORE-AVX2")
  else(COMPILER_SUPPORTS_AVX)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -xAVX -axCORE-AVX2.")
  endif(COMPILER_SUPPORTS_AVX)

  cmake_push_check_state()
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++11")
  check_cxx_source_runs("
  #include <memory>

  int main()
  {
    std::size_t alignment = 32;
    std::size_t size = 32;
    std::size_t space = 32;
    void* p = nullptr;

    std::align(alignment, size, p, space);

    return 0;
  }
" HAS_STD_ALIGN2)
  cmake_pop_check_state()

  if(NOT HAS_STD_ALIGN2)
    add_definitions(-DNEED_STD_ALIGN)
  endif(NOT HAS_STD_ALIGN2)

  CHECK_CXX_COMPILER_FLAG("-Werror=suggest-override" COMPILER_HAS_SUGGEST_OVERRIDE)
  if(COMPILER_HAS_SUGGEST_OVERRIDE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=suggest-override")
  else(COMPILER_HAS_SUGGEST_OVERRIDE)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -Werror=suggest-override.")
  endif(COMPILER_HAS_SUGGEST_OVERRIDE)

  if(DISABLE_EIGEN_WARNINGS)
    CHECK_CXX_COMPILER_FLAG("-Wno-deprecated-declarations" COMPILER_SUPPORTS_DEPRECATED_DECLARATIONS)
    if(COMPILER_SUPPORTS_DEPRECATED_DECLARATIONS)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    else(COMPILER_SUPPORTS_DEPRECATED_DECLARATIONS)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -Wno-deprecated-declarations.")
    endif(COMPILER_SUPPORTS_DEPRECATED_DECLARATIONS)

    CHECK_CXX_COMPILER_FLAG("-Wno-ignored-attributes" COMPILER_SUPPORTS_IGNORED_ATTRIBUTES)
    if(COMPILER_SUPPORTS_IGNORED_ATTRIBUTES)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-attributes")
    else(COMPILER_SUPPORTS_IGNORED_ATTRIBUTES)
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} doesn't support -Wno-ignored-attributes.")
    endif(COMPILER_SUPPORTS_IGNORED_ATTRIBUTES)
  endif(DISABLE_EIGEN_WARNINGS)
