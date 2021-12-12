CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(CMAKE_CXX_FLAGS                     "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -W")

OPTION(WORKMODE    "WORK MODE SELECT"  OFF)

SET(main_dir                            "${CMAKE_CURRENT_SOURCE_DIR}")
SET(baseAlg_dir                       "${main_dir}/../BaseAlgorithm")


IF(WORKMODE)
    SET(base_dir                        "/home/users/andrew2_liu/thirdlibrary")
ELSE()
    SET(base_dir                         "/usr/local")
ENDIF()

INCLUDE_DIRECTORIES(
    "${baseAlg_dir}"
    "${base_dir}/include"
)

FILE(GLOB   app_src
"${main_dir}/*.cpp"
)

LINK_DIRECTORIES(
    "${base_dir}/lib"
IF(NOT WORKMODE)
    "${base_dir}/lib64"
ENDIF()
)

ADD_SUBDIRECTORY("${baseAlg_dir}"                 baseAlg_dir)


ADD_EXECUTABLE(${PROJECT_NAME}  ${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  gtest pthread baseAlg)