cmake_minimum_required(VERSION 3.20)
project(mite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

# Include FetchContent module
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Set raylib configuration options
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)    # don't build the supplied example games

# Set Google Test configuration options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make both libraries available
FetchContent_MakeAvailable(raylib googletest)

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
        include/modules/mite/square.ixx
        include/modules/mite/rect.ixx
)

# Link raylib to the mite target
target_link_libraries(mite raylib)

# Enable testing
enable_testing()

# Create a test executable (optional - you can add test files later)
# add_executable(mite_tests
#     tests/test_point.cpp
#     tests/test_size.cpp
#     tests/test_square.cpp
#     tests/test_rect.cpp
# )
#
# target_sources(mite_tests
#     PUBLIC
#     FILE_SET CXX_MODULES
#     FILES
#     include/modules/mite/flat/point.ixx
#     include/modules/mite/flat/size.ixx
#     include/modules/mite/square.ixx
#     include/modules/mite/rect.ixx
# )
#
# target_link_libraries(mite_tests
#     gtest_main
#     gmock_main
# )
#
# include(GoogleTest)
# gtest_discover_tests(mite_tests)

# Platform-specific configurations
if(WIN32)
    target_link_libraries(mite winmm)
elseif(APPLE)
    target_link_libraries(mite "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(mite m dl pthread GL X11)
endif()
