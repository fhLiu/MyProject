CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_blog)

FILE(GLOB  blog_src
"${blog_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${blog_src})