project("${PROJECT_NAME}_Epoch" LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  example.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar_static-data
)
