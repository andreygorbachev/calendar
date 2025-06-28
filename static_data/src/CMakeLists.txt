# project "calendar_static-data"

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
  ../include/static_data.h # should target_include_directories take care of a pathe here?
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  calendar
)

#export(TARGETS calendar_static-data NAMESPACE Calendar::StaticData:: FILE CalendarStaticDataConfig.cmake)
