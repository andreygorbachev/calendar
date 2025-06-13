project("${PROJECT_NAME}_K.8" LANGUAGES CXX)

add_library(${PROJECT_NAME}
  calendar-K.8.cpp
  calendar-K.8.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
