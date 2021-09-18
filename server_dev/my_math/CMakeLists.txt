CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(my_math)

FILE(GLOB	math_src
"${math_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${math_src})