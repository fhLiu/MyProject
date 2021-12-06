CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(RedisApp)

option(WORKMODE  "Build for work mode" OFF)

add_definitions(
    -UWORKMODE
)

SET(main_dir                    "${CMAKE_CURRENT_SOURCE_DIR}")
SET(utiltools_dir               "${main_dir}/utiltools")
IF(WORKMODE)
    SET(base_dir                    "/home/users/andrew2_liu/thirdlibrary")
ELSE()
    SET(base_dir                    "/usr/local")
ENDIF()
SET(login_dir                   "${main_dir}/login")
SET(fans_dir                    "${main_dir}/fans")
SET(timeline_dir                "${main_dir}/timeline")
SET(blog_dir                    "${main_dir}/blog")

SET(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS} -std=c++11 -W -g -pthread")

INCLUDE_DIRECTORIES(
"${base_dir}/include"
"${utiltools_dir}"
)

LINK_DIRECTORIES(
    "${base_dir}/lib"
IF(NOT WORKMODE)
    "${base_dir}/lib64"
ENDIF()
)

ADD_SUBDIRECTORY("${utiltools_dir}"                             re_utiltools)
ADD_SUBDIRECTORY("${login_dir}"                                 re_login)
ADD_SUBDIRECTORY("${fans_dir}"                                  re_fans)
ADD_SUBDIRECTORY("${timeline_dir}"                              re_timeline)
ADD_SUBDIRECTORY("${blog_dir}"                                  re_blog)


FILE(GLOB        main_src
"${main_dir}/*.cpp"
"${login_dir}/*.cc"
"${fans_dir}/*.cc"
"${timeline_dir}/*.cc"
"${blog_dir}/*.cc"
"${utiltools_dir}/*.cc"
)

ADD_EXECUTABLE(${PROJECT_NAME}      ${main_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}   gtest hiredis pthread re_utiltools re_login re_blog re_timeline re_fans)