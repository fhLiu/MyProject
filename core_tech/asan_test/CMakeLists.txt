CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(asan_test)

FILE(GLOB   asan_src
"${asan_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}  SHARED  ${asan_src})