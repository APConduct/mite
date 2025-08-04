cmake_minimum_required(VERSION 3.28)
project(mite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Create the module library
add_library(mite_modules STATIC)

target_sources(mite_modules
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

target_include_directories(mite_modules
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/modules/mite>
    $<INSTALL_INTERFACE:include>
)

# Create the main executable
add_executable(mite)

target_sources(mite PRIVATE
    src/main.cpp
)

target_include_directories(mite
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/modules/mite>
)

# Link the module library to the executable
target_link_libraries(mite PRIVATE mite_modules raylib)

# Platform-specific configurations
if(WIN32)
    target_link_libraries(mite PRIVATE winmm)
elseif(APPLE)
    target_link_libraries(mite PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(mite PRIVATE m dl pthread GL X11)
endif()

# Enable testing
enable_testing()

# Create test executable
add_executable(mite_tests
    tests/test_basic.cpp
    tests/test_flat_point.cpp
)

target_link_libraries(mite_tests
    PRIVATE
    mite_modules
    gtest_main
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(mite_tests)
