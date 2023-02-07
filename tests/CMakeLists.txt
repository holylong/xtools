
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE TEST_SRCS RELATIVE ${TEST_DIR} ${TEST_DIR}/*.c ${TEST_DIR}/*.cc)

message(STATUS "==>> ${TEST_SRCS}")

include_directories(${CMAKE_SOURCE_DIR}/include)

foreach(tfile IN LISTS TEST_SRCS)
	get_filename_component(tname ${tfile} NAME_WE)
	add_executable(${tname} ${tfile})
	target_include_directories(${tname} PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/json/single_include)
	if(MSVC)
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)

	if(UNIX)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration")
	endif(UNIX)
endforeach(tfile IN LISTS TEST_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
