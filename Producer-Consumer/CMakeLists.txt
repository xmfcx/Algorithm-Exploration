cmake_minimum_required(VERSION 3.7)
project(ProducerConsumer)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

set(SOURCE_FILES main.cpp)
add_executable(ProducerConsumer ${SOURCE_FILES})

target_link_libraries(ProducerConsumer ${CMAKE_THREAD_LIBS_INIT})