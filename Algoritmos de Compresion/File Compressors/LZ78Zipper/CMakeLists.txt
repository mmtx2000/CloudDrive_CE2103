cmake_minimum_required(VERSION 3.22)
project(LZ78_Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(LZ78_Algorithm main.cpp PCRFile.cpp PCRFile.h LZ78.cpp LZ78.h Handler.cpp Handler.h)
