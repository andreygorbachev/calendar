project("${PROJECT_NAME}_performance" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  SONIA.cpp
  London.cpp
  London.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
