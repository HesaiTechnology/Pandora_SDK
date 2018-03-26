cmake_minimum_required(VERSION 2.8)
project(Pandora)


find_package( Boost REQUIRED )
find_package(PCL REQUIRED COMPONENTS common)
find_packege(OpenCV)

set (CMAKE_CXX_FLAGS "-g -fPIC --std=c++11")


include_directories(
	.
	include
	${Boost_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)


add_library( ${PROJECT_NAME}
	src/pandora.cc
)

target_link_libraries(${PROJECT_NAME}
		Pandar40P
		${Boost_LIBRARIES}
		${PCL_IO_LIBRARIES}
)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	

	add_executable(pandar40_test
		test/test.cc
	)

	target_link_libraries(pandar40_test
		${PROJECT_NAME}
		${Boost_LIBRARIES}
		${PCL_IO_LIBRARIES}
	)

endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

