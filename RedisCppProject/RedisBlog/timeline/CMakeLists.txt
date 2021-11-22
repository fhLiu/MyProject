CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_timeline)

FILE(GLOB  timeline_src
"${timeline_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} -SHARED ${timeline_src})