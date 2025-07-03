project("${PROJECT_NAME}_CSV" LANGUAGES CXX)

configure_file(data/NYM.csv NYM.csv COPYONLY)
configure_file(data/TYO.csv TYO.csv COPYONLY)
configure_file(data/NNT.csv NNT.csv COPYONLY)

add_executable(${PROJECT_NAME}
  example.cpp
  parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)

# to make IDE to show this file as part of the project
target_sources(${PROJECT_NAME} PRIVATE
  data/NYM.csv
  data/TYO.csv
  data/NNT.csv
)
