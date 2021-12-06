CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(re_blog)

INCLUDE_DIRECTORIES(
    "${utiltools_dir}"
)

FILE(GLOB  blog_src
"${blog_dir}/*.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${blog_src})