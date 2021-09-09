CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(main_dir		${CMAKE_CURRENT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++11 -g -w -O2 -pthread")


FILE(GLOB  app_src
"${main_dir}/*.cpp"	
)

ADD_EXECUTABLE(${PROJECT_NAME}	${app_src})
