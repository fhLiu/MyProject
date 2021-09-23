CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(client)

SET(cli_dir					"${CMAKE_CURRENT_SOURCE_DIR}")
SET(tcp_dir					"${cli_dir}/..")

FILE(GLOB	cli_src
"${cli_dir}/*.cpp"
)

INCLUDE_DIRECTORIES(
${tcp_dir}
)

add_definitions(
	-DSIGNAL_RUN
)

ADD_EXECUTABLE(${PROJECT_NAME}		${cli_src})