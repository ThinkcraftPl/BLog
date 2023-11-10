cmake_minimum_required(VERSION 3.27)

# Git versioning
find_package(Git)

if(GIT_EXECUTABLE)
  # execute git describe to get the dirty version
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --match "v*"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(GIT_VERSION "${GIT_DESCRIBE_VERSION}")
  endif()
endif()

if(NOT DEFINED GIT_VERSION)
  set(GIT_VERSION "v0.0.0")
endif()

string(REGEX REPLACE "^v" "" GIT_VERSION "${GIT_VERSION}")
string(REGEX REPLACE "-[^-]*$" "" GIT_VERSION "${GIT_VERSION}")
string(REGEX REPLACE "-" "." GIT_VERSION "${GIT_VERSION}")

message("Version: ${GIT_VERSION}")

set(PROJECT_NAME BLog)
project(${PROJECT_NAME} VERSION ${GIT_VERSION} LANGUAGES CXX)

file(GLOB CPPFiles src/*.cpp src/**/*.cpp)
file(GLOB HPPFiles include/BLog/*.hpp include/BLog/*.hpp)

add_library(${PROJECT_NAME} STATIC ${CPPFiles} ${HPPFiles})
target_include_directories(${PROJECT_NAME} PUBLIC include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dependencies/date)
target_link_libraries(${PROJECT_NAME} date::date)
add_dependencies(${PROJECT_NAME} date::date)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

add_executable(${PROJECT_NAME}_sandbox sandbox.cpp)
target_link_libraries(${PROJECT_NAME}_sandbox ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME}_sandbox ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}_sandbox PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)