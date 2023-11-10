cmake_minimum_required(VERSION 3.27)

# Git versioning
find_package(Git)

if(GIT_EXECUTABLE)
  # execute git describe to get the dirty version
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --match --always "v*"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(GIT_VERSION "${GIT_DESCRIBE_VERSION}")
  endif()
endif()

message("Version: ${GIT_VERSION}")