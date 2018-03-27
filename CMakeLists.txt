cmake_minimum_required(VERSION 2.8)
project(Pandora)


find_package( Boost REQUIRED )
find_package( PCL REQUIRED COMPONENTS common )
find_package( OpenCV REQUIRED )

set (CMAKE_CXX_FLAGS "-fPIC --std=c++11")

add_subdirectory(src/Pandar40P)

include_directories(
	.
	include
	src/Pandar40P/include
	${Boost_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)


add_library( ${PROJECT_NAME} SHARED
	src/pandora.cc
	src/pandora_client.c
	src/pandora_camera.cc
	src/util.c
	src/tcp_command_client.c
)

target_link_libraries(${PROJECT_NAME} 
		Pandar40P
		${Boost_LIBRARIES}
		${PCL_IO_LIBRARIES}
		${OpenCV_LIBS}
		yaml-cpp
		jpeg
)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	

	add_executable(pandora_test
		test/test.cc
	)

	target_link_libraries(pandora_test
	  Pandar40P
		${PROJECT_NAME}
		${Boost_LIBRARIES}
		${PCL_IO_LIBRARIES}
		${OpenCV_LIBS}
		yaml-cpp
		jpeg
	)

endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

