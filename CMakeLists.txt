cmake_minimum_required(VERSION 3.27)

project(2d-game VERSION 0.0.1 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

include(cmake/get_cpm.cmake)
CPMUsePackageLock(package-lock.cmake)

find_package(EASTL)

add_subdirectory(modules/window)

add_executable(main main.cpp)
target_link_libraries(main engine::window)