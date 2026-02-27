cmake_minimum_required(VERSION 3.16)
project(sync-backend VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Crow (header-only HTTP framework)
include(FetchContent)
FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG        v1.0+5
)
FetchContent_MakeAvailable(Crow)

# Collect source files
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

# Build type defaults
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:Release>:-O2>
)
