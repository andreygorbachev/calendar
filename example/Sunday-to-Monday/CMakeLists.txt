project("${PROJECT_NAME}_Sunday-to-Monday" LANGUAGES CXX)
# should it be called K.8?

add_executable(${PROJECT_NAME}
  example.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
