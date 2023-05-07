project(calendar_test)

#add_executable(Easter_test
#  Easter.cpp
#)
#
#target_link_libraries(Easter_test PRIVATE
#  calendar
#)

add_executable(${PROJECT_NAME}
  basic_calendar.cpp
  calendar.cpp
  business_days.cpp
  ics_parser.cpp
  setup.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
