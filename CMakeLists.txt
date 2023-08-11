cmake_minimum_required(VERSION 3.25)
project(cml)

set(CMAKE_CXX_STANDARD 17)

add_executable(cml main.cpp utils/FileHandle/FileHandle.h utils/FileHandle/FileHandle.cpp cv/Image/Image.cpp cv/Image/Image.h)
