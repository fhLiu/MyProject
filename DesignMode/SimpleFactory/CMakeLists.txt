CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(simplefac)

FILE(GLOB   simplefac_src
"${simplefac_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${simplefac_src})