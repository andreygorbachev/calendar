cmake_minimum_required(VERSION 3.15)

project("calendar" VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

option(CALENDAR_BUILD_TESTS_AND_EXAMPLES "Build all of calendar's own tests and examples." On)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

  include(FetchContent)

  set(BUILD_GMOCK Off) # I am not sure if this meant to be used outside of googletest

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
  )

  FetchContent_MakeAvailable(googletest)

  enable_testing()

endif()

add_subdirectory(util)

add_subdirectory(include)

add_subdirectory(static_data)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)
  add_subdirectory(performance)
  add_subdirectory(example)

endif()

#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE Calendar)
