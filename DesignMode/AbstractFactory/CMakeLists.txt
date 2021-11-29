CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(abstractfac)


FILE(GLOB   abstractfac_src
"${abstractfac_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${abstractfac_src})