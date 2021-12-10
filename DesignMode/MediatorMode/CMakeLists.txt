CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(mediator)

FILE(GLOB   mediator_src
"${mediator_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${mediator_src})