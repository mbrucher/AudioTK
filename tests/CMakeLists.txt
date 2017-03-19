
file(GLOB entries *)
foreach(entry ${entries})
  if(IS_DIRECTORY ${entry} AND EXISTS ${entry}/CMakeLists.txt)
    add_subdirectory(${entry})
  endif()
endforeach(entry)

