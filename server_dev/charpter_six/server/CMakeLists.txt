CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(server)

SET(ser_dir					"${CMAKE_CURRENT_SOURCE_DIR}")
SET(tcp_dir					"${ser_dir}/..")

INCLUDE_DIRECTORIES(
${tcp_dir}
)

FILE(GLOB	ser_src
"${ser_dir}/*.cpp"
)

add_definitions(
	-DSIGNAL_RUN
)

ADD_EXECUTABLE(${PROJECT_NAME}		${ser_src})