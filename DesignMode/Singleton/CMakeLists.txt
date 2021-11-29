CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(singleton)


FILE(GLOB   singleton_src
"${singleton_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${singleton_src})