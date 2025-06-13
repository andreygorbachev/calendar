project("${PROJECT_NAME}_T2" LANGUAGES CXX)

add_library(${PROJECT_NAME}
  calendar_T2.cpp
  calendar_T2.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
