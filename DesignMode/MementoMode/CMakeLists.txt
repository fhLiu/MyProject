CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(mementor)

FILE(GLOB   mementor_src
"${mementor_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${mementor_src})