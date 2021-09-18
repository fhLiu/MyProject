CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(ser_tcp)

FILE(GLOB	tcp_src
"${tcp_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${tcp_dir})