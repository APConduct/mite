cmake_minimum_required(VERSION 3.20)
project(mite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)



add_executable(mite)

target_sources(mite PRIVATE
    src/main.cpp
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        include/modules/mite/mite.ixx
        include/modules/mite/flat/point.ixx
        include/modules/mite/flat/size.ixx
        include/modules/mite/flat/mod.ixx
)