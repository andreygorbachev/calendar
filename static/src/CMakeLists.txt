# project "calendar_static"

add_library(${PROJECT_NAME}
  UK.cpp
  EU.cpp
  USA.cpp
  Brazil.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ../include
)

# to make IDE to show this file as part of the project
target_sources(${PROJECT_NAME} PRIVATE
  ../include/static.h # probably not the best name as static is a C++ keyword
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar_util
  calendar
)
