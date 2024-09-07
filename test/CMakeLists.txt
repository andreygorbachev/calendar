project(calendar-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
  weekend.cpp
  period.cpp
  time_series.cpp
  schedule.cpp
  calendar.cpp
  annual_holidays.cpp
  business_day_conventions.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
