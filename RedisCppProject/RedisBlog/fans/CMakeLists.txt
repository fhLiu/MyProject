CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_fans)

FILE(GLOB  fans_src
"${fans_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} -SHARED ${fans_src})