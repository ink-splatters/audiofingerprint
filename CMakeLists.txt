cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project (AudioFingerPrint)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
SET(CMAKE_CXX_FLAGS "-std=c++0x")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package( Boost 1.55 COMPONENTS system program_options REQUIRED )

find_package(GracenoteSDK 3.07.7 REQUIRED)

set (GRACENOTESDK_CPP_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/wrappers/gnsdk_cplusplus/src_wrapper)

add_definitions(-DGNSDK_STORAGE_SQLITE=1)
add_definitions(-DGNSDK_MUSICID=1)
add_definitions(-DGNSDK_MUSICID_STREAM=1)

file (GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file (GLOB WRAPPER_SRC ${GRACENOTESDK_CPP_INCLUDE_DIR}/*.cpp)

include_directories( ${Boost_INCLUDE_DIR} )
include_directories (${CMAKE_SOURCE_DIR})
include_directories (${GRACENOTESDK_INCLUDE_DIR})
include_directories (${GRACENOTESDK_CPP_INCLUDE_DIR})
include_directories (${GRACENOTESDK_PLATFORM_INCLUDE_DIR})
link_directories(${GRACENOTESDK_LIB_DIR})

add_executable(${PROJECT_NAME} ${SRC} ${WRAPPER_SRC})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${GRACENOTESDK_LIBRARIES} )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

# Install 
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}) 
install(CODE "
    execute_process(COMMAND ${CMAKE_COMMAND} -DGRACENOTESDK_LIB_DIR=${GRACENOTESDK_LIB_DIR} -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -P ${CMAKE_SOURCE_DIR}/install.cmake)
")
