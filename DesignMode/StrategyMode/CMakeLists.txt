CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(strategy)

FILE(GLOB   strategy_src
"${strategy_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${strategy_src})