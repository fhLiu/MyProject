CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(responsibility)

FILE(GLOB   responsibility_src
"${responsibility_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${responsibility_src})