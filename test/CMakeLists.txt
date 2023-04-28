add_executable(basic_calendar
  basic_calendar.cpp
)

target_link_libraries(basic_calendar PRIVATE
  calendar
)
