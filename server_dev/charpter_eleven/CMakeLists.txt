CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(communication_pro)

FILE(GLOB	communication_pro_src
"${communication_pro_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME}	 SHARED	${communication_pro_src})