cmake_minimum_required (VERSION 3.1.3 FATAL_ERROR)
project(local_proxy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(ZMQ)
if(ZMQ_FOUND)
  link_libraries(${ZMQ_LIBRARY})
  include_directories(${ZMQ_INCLUDE_DIR})
endif()

add_executable(local_proxy src/main.cpp src/zmq_proxy.cpp)
add_executable(pub src/pub.cpp)
add_executable(sub src/sub.cpp)

install (TARGETS local_proxy pub sub DESTINATION bin)

set_target_properties(local_proxy pub sub PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

if(ZMQ_FOUND)
  set_target_properties(local_proxy pub sub PROPERTIES COMPILE_DEFINITIONS "WITH_ZMQ=1")
else()
  set_target_properties(local_proxy pub sub PROPERTIES COMPILE_DEFINITIONS "WITH_ZMQ=0")
endif()
