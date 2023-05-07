project(calendar_test)

#add_executable(basic_calendar_test
#  basic_calendar.cpp
#)
#
#target_link_libraries(basic_calendar_test PRIVATE
#  calendar
#)
#
#
#add_executable(calendar_test
#  calendar.cpp
#)
#
#target_link_libraries(calendar_test PRIVATE
#  calendar
#)
#
#
#add_executable(business_days_test
#  business_days.cpp
#)
#
#target_link_libraries(business_days_test PRIVATE
#  calendar
#)
#
#
#add_executable(Easter_test
#  Easter.cpp
#)
#
#target_link_libraries(Easter_test PRIVATE
#  calendar
#)

add_executable(${PROJECT_NAME}
  business_days.cpp
  ics_parser.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
