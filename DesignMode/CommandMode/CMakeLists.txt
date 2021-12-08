CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(command_mode)

FILE(GLOB   command_src
"${command_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${command_src})