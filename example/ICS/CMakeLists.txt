project("${PROJECT_NAME}_ICS" LANGUAGES CXX)

configure_file(data/england-and-wales.ics england-and-wales.ics COPYONLY)
configure_file(data/scotland.ics scotland.ics COPYONLY)
configure_file(data/northern-ireland.ics northern-ireland.ics COPYONLY)
configure_file(data/united-states.ics united-states.ics COPYONLY)

add_executable(${PROJECT_NAME}
  example.cpp
  parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
