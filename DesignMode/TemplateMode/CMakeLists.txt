CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(template)

FILE(GLOB   template_src
"${template_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${template_src})