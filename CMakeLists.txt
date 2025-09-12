cmake_minimum_required(VERSION 3.10)
project(CppJsonParser)

set(CMAKE_CXX_STANDARD 17)

# 源文件
set(SOURCES
    # src/main.cpp
    test_main.cpp
    src/JsonValue.h
)

add_executable(CppJsonParser ${SOURCES})

# 包含头文件目录
include_directories(src)
