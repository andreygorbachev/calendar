project("${PROJECT_NAME}_ICS" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  example.cpp
  parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
