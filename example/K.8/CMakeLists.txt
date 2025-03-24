project("calendar-example-K.8")

add_library(${PROJECT_NAME}
  calendar-K.8.cpp
  calendar-K.8.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
