CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(adapter)

FILE(GLOB   adapter_src
"${adapter_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${adapter_src})