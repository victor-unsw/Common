cmake_minimum_required(VERSION 3.2)
project(EmailParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c parser.c parser.h)
add_executable(EmailParser ${SOURCE_FILES} parser.h parser.c)