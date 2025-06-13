project("${PROJECT_NAME}-util" LANGUAGES NONE)

add_subdirectory(include)

if(NOT GREGORIAN_CALENDAR_MINIMAL)

	enable_testing()

	add_subdirectory(test)

endif()
