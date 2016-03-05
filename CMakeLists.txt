cmake_minimum_required (VERSION 3.1.3 FATAL_ERROR)
project(local_proxy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set a default build type for single-configuration
# CMake generators if no build type is set.
IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(ZMQ REQUIRED)
include_directories(${ZMQ_INCLUDE_DIR})

add_executable(zmq_local_proxy src/main.cpp)
target_link_libraries(zmq_local_proxy ${ZMQ_LIBRARY})
install (TARGETS zmq_local_proxy DESTINATION bin)
set_property(TARGET zmq_local_proxy PROPERTY CXX_STANDARD 11)
set_property(TARGET zmq_local_proxy PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(pub src/pub.cpp)
target_link_libraries(pub ${ZMQ_LIBRARY})
install (TARGETS pub DESTINATION bin)
set_property(TARGET pub PROPERTY CXX_STANDARD 11)
set_property(TARGET pub PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(sub src/sub.cpp)
target_link_libraries(sub ${ZMQ_LIBRARY})
install (TARGETS sub DESTINATION bin)
set_property(TARGET sub PROPERTY CXX_STANDARD 11)
set_property(TARGET sub PROPERTY CXX_STANDARD_REQUIRED ON)
