CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(ser_tcp)

FILE(GLOB	tcp_src
"${tcp_dir}/server/*.cpp"
"${tcp_dir}/client/*.cpp"
)

INCLUDE_DIRECTORIES(
"${tcp_dir}/server"
"${tcp_dir}/client"
)

add_definitions(
	-USIGNAL_RUN
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${tcp_src})