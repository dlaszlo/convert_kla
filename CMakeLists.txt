cmake_minimum_required(VERSION 3.9.1)

project(KLAConvert)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(convert convert.c fade.c koala.c options.c utils.c)
