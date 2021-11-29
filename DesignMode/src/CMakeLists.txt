CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(CMAKE_CXX_FLAGS                     "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -W")

OPTION(WORKMODE    "WORK MODE SELECT"  ON)

SET(main_dir                            "${CMAKE_CURRENT_SOURCE_DIR}")
SET(singleton_dir                       "${main_dir}/../Singleton")
SET(simplefac_dir                       "${main_dir}/../SimpleFactory")
SET(abstractfac_dir                     "${main_dir}/../AbstractFactory")
IF(WORKMODE)
    SET(base_dir                    "/home/users/andrew2_liu/thirdlibrary")
ELSE()
    SET(base_dir                    "/usr/local")
ENDIF()

INCLUDE_DIRECTORIES(
    "${singleton_dir}"
    "${simplefac_dir}"
    "${abstractfac_dir}"
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

ADD_SUBDIRECTORY("${singleton_dir}"              singleton)
ADD_SUBDIRECTORY("${simplefac_dir}"              simplefac)
ADD_SUBDIRECTORY("${abstractfac_dir}"            abstractfac)


ADD_EXECUTABLE(${PROJECT_NAME}  ${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  gtest pthread singleton simplefac abstractfac)