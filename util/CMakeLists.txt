project("${PROJECT_NAME}_util" LANGUAGES NONE)

add_subdirectory(include)

if(${CALENDAR_BUILD_TESTS_AND_EXAMPLES})

	enable_testing()

	add_subdirectory(test)

endif()
