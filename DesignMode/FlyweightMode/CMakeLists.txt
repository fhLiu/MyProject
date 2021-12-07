CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(flyweight)

FILE(GLOB   flyweight_src
"${flyweight_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${flyweight_src})