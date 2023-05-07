project(calendar_test)

add_executable(${PROJECT_NAME}
  basic_calendar.cpp
  calendar.cpp
  business_days.cpp
  Easter.cpp
  ics_parser.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
