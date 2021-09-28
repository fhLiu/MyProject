CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(main_dir				${CMAKE_CURRENT_SOURCE_DIR})
SET(math_dir				"${main_dir}/../my_math")
SET(tcp_dir					"${main_dir}/../charpter_six")
SET(mul_thread_dir          "${main_dir}/../charpter_nine")
SET(mul_proccess_dir        "${main_dir}/../charpter_ten")
SET(communication_pro_dir   "${main_dir}/../charpter_eleven")

SET(CMAKE_CXX_FLAGS			"${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -pthread")

INCLUDE_DIRECTORIES(
"${math_dir}"
"${tcp_dir}"
"${mul_thread_dir}"
"${mul_proccess_dir}"
"${communication_pro_dir}"
)

FILE(GLOB	app_src
"${main_dir}/*.cpp"
)

ADD_SUBDIRECTORY(${math_dir}			    my_math)
ADD_SUBDIRECTORY(${tcp_dir}			        ser_tcp)
ADD_SUBDIRECTORY(${mul_thread_dir}	        mul_thread)
ADD_SUBDIRECTORY(${mul_proccess_dir}	    mul_proccess)
ADD_SUBDIRECTORY(${communication_pro_dir}	    communication_pro)

ADD_EXECUTABLE(${PROJECT_NAME}	${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}	my_math ser_tcp pthread mul_thread mul_proccess communication_pro)