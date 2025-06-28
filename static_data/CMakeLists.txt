project("${PROJECT_NAME}_static-data" LANGUAGES CXX)

add_subdirectory(src)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)

endif()
