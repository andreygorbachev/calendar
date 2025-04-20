project("calendar-example-T2")

add_library(${PROJECT_NAME}
  calendar-T2.cpp
  calendar-T2.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
