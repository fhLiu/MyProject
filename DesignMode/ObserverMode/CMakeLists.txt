CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(observer)

FILE(GLOB   observer_src
"${observer_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${observer_src})