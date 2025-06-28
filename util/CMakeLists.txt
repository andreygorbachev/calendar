project("${PROJECT_NAME}_util" LANGUAGES CXX)

add_subdirectory(include)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)

endif()
