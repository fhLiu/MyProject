CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_utiltools)

FILE(GLOB  utiltools_src
"${utiltools_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} -SHARED ${utiltools_src})