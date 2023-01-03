
set(CMD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE CMD_SRCS RELATIVE ${CMD_DIR} ${CMD_DIR}/*.c)

message(STATUS "==>> ${CMD_SRCS}")

foreach(cmdfile IN LISTS CMD_SRCS)
	get_filename_component(cmdname ${cmdfile} NAME_WE)
	add_executable(${cmdname} ${cmdfile})
	if(MSVC)
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)
endforeach(cmdfile IN LISTS CMD_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
