project("calendar-example-performance")

add_executable(${PROJECT_NAME}
  SONIA.cpp
  SONIA.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
