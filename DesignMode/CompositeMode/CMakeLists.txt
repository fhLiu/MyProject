CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(composite)

FILE(GLOB   composite_src
"${composite_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${composite_src})