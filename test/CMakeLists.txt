project(calendar_test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  weekend.cpp
  period.cpp
  schedule.cpp
  calendar.cpp
  annual_holidays.cpp
  business_day_conventions.cpp
  ics_parser.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
)
