add_executable(basic_calendar_test
  basic_calendar.cpp
)

target_link_libraries(basic_calendar_test PRIVATE
  calendar
)


add_executable(calendar_test
  calendar.cpp
)

target_link_libraries(calendar_test PRIVATE
  calendar
)


add_executable(Easter_test
  Easter.cpp
)

target_link_libraries(Easter_test PRIVATE
  calendar
)
