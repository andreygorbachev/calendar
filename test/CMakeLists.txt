project("${PROJECT_NAME}_test" LANGUAGES CXX)

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
