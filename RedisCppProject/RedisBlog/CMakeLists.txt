CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(RedisApp)

option(WORKMODE  "Build for work mode" ON)

add_definitions(
    -DWORKMODE
)

SET(main_dir                    "${CMAKE_CURRENT_SOURCE_DIR}")
IF(WORKMODE)
    SET(base_dir                    "/home/users/andrew2_liu/thirdlibrary")
ELSE()
    SET(base_dir                    "/usr/local")
ENDIF()
SET(login_dir                   "${main_dir}/login")
SET(fans_dir                    "${main_dir}/fans")
SET(timeline_dir                "${main_dir}/timeline")
SET(blog_dir                    "${main_dir}/blog")
SET(utiltools_dir               "${main_dir}/utiltools")

SET(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS} -std=c++11 -W -g -pthread")

INCLUDE_DIRECTORIES(
"${base_dir}/include"
)

LINK_DIRECTORIES(
    "${base_dir}/lib"
IF(NOT WORKMODE)
    "${base_dir}/lib64"
ENDIF()
)

ADD_SUBDIRECTORY("${login_dir}"                                 re_login)
ADD_SUBDIRECTORY("${fans_dir}"                                  re_fans)
ADD_SUBDIRECTORY("${timeline_dir}"                              re_timeline)
ADD_SUBDIRECTORY("${blog_dir}"                                  re_blog)
ADD_SUBDIRECTORY("${utiltools_dir}"                             re_utiltools)


FILE(GLOB        main_src
"${main_dir}/*.cpp"
)

ADD_EXECUTABLE(${PROJECT_NAME}      ${main_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}   gtest hiredis pthread re_login re_blog re_timeline re_utiltools re_fans)