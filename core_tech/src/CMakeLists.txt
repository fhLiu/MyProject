CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

OPTION(ASAN_USED "DEBUG USED ASAN LIB" OFF)
OPTION(VALGRIND "DEBUG USED VALGRIND TOOLS" ON)

SET(main_dir		${CMAKE_CURRENT_SOURCE_DIR})
SET(asan_dir        "${main_dir}/../asan_test")
IF(ASAN_USED)
    SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++11 -g1 -w -O2 -pthread -fsanitize=address -fno-stack-protector -fno-omit-frame-pointer -fno-var-tracking")
ELSEIF(VALGRIND)
    SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++11 -g -w -O -pthread")
ELSE()
    SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++11 -g -w -O -pthread")
ENDIF()


INCLUDE_DIRECTORIES(
    "${asan_dir}"
)

FILE(GLOB  app_src
"${main_dir}/*.cpp"	
)

ADD_SUBDIRECTORY(${asan_dir}            asan_test)


ADD_EXECUTABLE(${PROJECT_NAME}	${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} pthread asan_test)
