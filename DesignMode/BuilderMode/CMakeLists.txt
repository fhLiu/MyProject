CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(builder)

FILE(GLOB   builder_src
"${builder_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${builder_src})