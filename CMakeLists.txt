cmake_minimum_required(VERSION 3.16)
project(UrlTop100)
include_directories(src/include)
aux_source_directory(src/main dir_srcs)
set(CMAKE_CXX_STANDARD 11)
set(WORK ${dir_srcs})
add_executable(work ${WORK} )