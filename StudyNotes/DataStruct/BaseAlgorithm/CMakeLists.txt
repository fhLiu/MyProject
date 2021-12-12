CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(baseAlg)

FILE(GLOB   baseAlg_src
"${baseAlg_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${baseAlg_src})