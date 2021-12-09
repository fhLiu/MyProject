CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(app)

SET(CMAKE_CXX_FLAGS                     "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -W")

OPTION(WORKMODE    "WORK MODE SELECT"  ON)

SET(main_dir                            "${CMAKE_CURRENT_SOURCE_DIR}")
SET(singleton_dir                       "${main_dir}/../Singleton")
SET(simplefac_dir                       "${main_dir}/../SimpleFactory")
SET(factorymethod_dir                   "${main_dir}/../FactoryMethod")
SET(builder_dir                         "${main_dir}/../BuilderMode")
SET(proxy_dir                           "${main_dir}/../ProxyMode")
SET(adapter_dir                         "${main_dir}/../AdapterMode")
SET(bridge_dir                          "${main_dir}/../BridgeMode")
SET(decorator_dir                       "${main_dir}/../DecoratorMode")
SET(flyweight_dir                       "${main_dir}/../FlyweightMode")
SET(composite_dir                       "${main_dir}/../CompositeMode")
SET(template_dir                        "${main_dir}/../TemplateMode")
SET(strategy_dir                        "${main_dir}/../StrategyMode")
SET(command_dir                         "${main_dir}/../CommandMode")
SET(responsibility_dir                  "${main_dir}/../ChainOfResponsibilityMode")

IF(WORKMODE)
    SET(base_dir                        "/home/users/andrew2_liu/thirdlibrary")
ELSE()
    SET(base_dir                         "/usr/local")
ENDIF()

INCLUDE_DIRECTORIES(
    "${singleton_dir}"
    "${simplefac_dir}"
    "${factorymethod_dir}"
    "${builder_dir}"
    "${proxy_dir}"
    "${adapter_dir}"
    "${bridge_dir}"
    "${decorator_dir}"
    "${flyweight_dir}"
    "${composite_dir}"
    "${template_dir}"
    "${strategy_dir}"
    "${command_dir}"
    "${responsibility_dir}"
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

ADD_SUBDIRECTORY("${singleton_dir}"                 singleton)
ADD_SUBDIRECTORY("${simplefac_dir}"                 simplefac)
ADD_SUBDIRECTORY("${factorymethod_dir}"             factorymethod)
ADD_SUBDIRECTORY("${builder_dir}"                   builder)
ADD_SUBDIRECTORY("${proxy_dir}"                     czproxy)
ADD_SUBDIRECTORY("${adapter_dir}"                   adapter)
ADD_SUBDIRECTORY("${bridge_dir}"                    bridge)
ADD_SUBDIRECTORY("${decorator_dir}"                 decorator)
ADD_SUBDIRECTORY("${flyweight_dir}"                 flyweight)
ADD_SUBDIRECTORY("${composite_dir}"                 composite)
ADD_SUBDIRECTORY("${template_dir}"                  template)
ADD_SUBDIRECTORY("${strategy_dir}"                  strategy)
ADD_SUBDIRECTORY("${command_dir}"                   command_mode)
ADD_SUBDIRECTORY("${responsibility_dir}"            responsibility)

ADD_EXECUTABLE(${PROJECT_NAME}  ${app_src})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  gtest pthread singleton simplefac factorymethod builder czproxy adapter bridge decorator flyweight 
composite template strategy command_mode responsibility)