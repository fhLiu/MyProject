CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(bridge)

FILE(GLOB   bridge_src
"${bridge_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${bridge_src})