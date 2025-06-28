project("${PROJECT_NAME}_static" LANGUAGES NONE)

add_subdirectory(src)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

  add_subdirectory(test)

endif()
