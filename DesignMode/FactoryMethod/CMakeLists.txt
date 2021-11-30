CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(factorymethod)


FILE(GLOB   factorymethod_src
"${factorymethod_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${factorymethod_src})