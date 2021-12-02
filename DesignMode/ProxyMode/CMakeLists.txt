CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(czproxy)

FILE(GLOB   czproxy_src
"${proxy_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${czproxy_src})