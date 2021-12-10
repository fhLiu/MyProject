CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(state_mode)

FILE(GLOB   state_mode_src
"${state_mode_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${state_mode_src})