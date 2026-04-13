project("${PROJECT_NAME}_K.8" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  example.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
