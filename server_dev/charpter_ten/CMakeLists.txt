CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(mul_proccess)

FILE(GLOB	mul_proccess_src
"${mul_proccess_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${mul_proccess_src})