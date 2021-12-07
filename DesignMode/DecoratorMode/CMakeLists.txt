CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(decorator)

FILE(GLOB   decorator_src
"${decorator_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${decorator_src})