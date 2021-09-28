CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(mul_thread)

FILE(GLOB	mul_thread_src
"${mul_thread_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${mul_thread_src})