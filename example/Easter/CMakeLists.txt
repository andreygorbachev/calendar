project("${PROJECT_NAME}_Easter" LANGUAGES CXX)

configure_file(data/easter500.txt easter500.txt COPYONLY)

add_executable(${PROJECT_NAME}
  example.cpp
  parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)

# to make IDE to show this file as part of the project
target_sources(${PROJECT_NAME} PRIVATE
  data/easter500.txt
)
