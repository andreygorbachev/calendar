project("Countries_example")

add_library(${PROJECT_NAME}
  calendars.cpp
  calendars.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
