project(calendar-test)

set(BUILD_GMOCK Off) # I am not sure if this meant to be used outside of googletest

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  weekend.cpp
  schedule.cpp
  calendar.cpp
  annual_holidays.cpp
  business_day_adjusters.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

add_subdirectory(util)
