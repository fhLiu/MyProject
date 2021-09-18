CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(main_dir				${CMAKE_CURRENT_SOURCE_DIR})
SET(math_dir				"${main_dir}/../my_math")
SET(tcp_dir					"${main_dir}/../charpter_six")

SET(CMAKE_CXX_FLAGS			"${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -pthread")

INCLUDE_DIRECTORIES(
"${math_dir}"
"${tcp_dir}"
)

FILE(GLOB	app_src
"${main_dir}/*.cpp"
)

ADD_SUBDIRECTORY(${math_dir}			my_math)
ADD_SUBDIRECTORY(${tcp_dir}			    ser_tcp)

ADD_EXECUTABLE(${PROJECT_NAME}	${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}	my_math ser_tcp pthread)