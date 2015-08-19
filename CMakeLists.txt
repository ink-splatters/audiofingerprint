cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project (AudioFingerPrint)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
SET(CMAKE_CXX_FLAGS "-std=c++0x")


find_package(GracenoteSDK 3.07.7 REQUIRED)
find_package(boost 1.58 COMPONENTS system property_tree program_options REQUIRED)

set (GRACENOTESDK_CPP_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/wrappers/gnsdk_cplusplus/src_wrapper)

file (GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file (GLOB WRAPPER_SRC ${GRACENOTESDK_CPP_INCLUDE_DIR}/*.cpp)


include_directories( ${Boost_INCLUDE_DIR} )
include_directories (${CMAKE_SOURCE_DIR})
include_directories (${GRACENOTESDK_INCLUDE_DIR})
include_directories (${GRACENOTESDK_CPP_INCLUDE_DIR})
include_directories (${GRACENOTESDK_PLATFORM_INCLUDE_DIR})
link_directories(${GRACENOTESDK_LIB_DIR})

message("!!! ${Boost_LIBRARIES}")

add_executable(${PROJECT_NAME} ${SRC} ${WRAPPER_SRC})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${GRACENOTESDK_LIBRARIES} )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)