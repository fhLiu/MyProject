CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_login)

INCLUDE_DIRECTORIES(
${utiltools_dir}
)

FILE(GLOB  login_src
"${login_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${login_src})