project("${PROJECT_NAME}_ANBIMA" LANGUAGES CXX)

configure_file(data/feriados_nacionais.csv feriados_nacionais.csv COPYONLY)

add_executable(${PROJECT_NAME}
  example.cpp
  parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  calendar
)
