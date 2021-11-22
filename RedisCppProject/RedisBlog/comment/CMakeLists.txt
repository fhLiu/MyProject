CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_comment)

FILE(GLOB  comment_src
"${comment_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} -SHARED ${comment_src})