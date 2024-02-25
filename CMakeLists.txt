cmake_minimum_required(VERSION 3.27)

cmake_policy(SET CMP0069 NEW)

project(2d-game VERSION 0.0.1 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  EASTL_DEBUGPARAMS_LEVEL=2
  EASTL_NAME_ENABLED
)


include(cmake/get_cpm.cmake)
CPMUsePackageLock(package-lock.cmake)

find_package(EASTL)
find_package(glm)

CPMAddPackage(
  GITHUB_REPOSITORY slembcke/Chipmunk2D
  GIT_TAG d0239ef4599b3688a5a336373f7d0a68426414ba
  GIT_SHALLOW
  OPTIONS
  "BUILD_DEMOS OFF"
  "INSTALL_DEMOS OFF"
  "BUILD_SHARED OFF"
  "BUILD_STATIC ON"
  "INSTALL_STATIC OFF"
  "LIB_INSTALL_DIR \"\""
  "BIN_INSTALL_DIR \"\""
)

add_subdirectory(modules/space)
add_subdirectory(modules/window)


add_executable(main main3.cpp
  tmp_stuff/StupidSpatial.cpp
  tmp_stuff/StupidSpatial.hpp)
target_link_libraries(main engine::window engine::space spdlog::spdlog chipmunk_static glm::glm)
target_include_directories(main PRIVATE ${Chipmunk2D_SOURCE_DIR}/include)