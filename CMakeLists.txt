cmake_minimum_required(VERSION 3.29)

cmake_policy(SET CMP0069 NEW)

project(2d-game VERSION 0.0.1 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  EASTL_DEBUGPARAMS_LEVEL=2
  EASTL_NAME_ENABLED
  GLM_ENABLE_EXPERIMENTAL
)


include(cmake/get_cpm.cmake)
CPMUsePackageLock(package-lock.cmake)


CPMAddPackage(
  NAME EABase 
#  VERSION 2.09.05
  URL "https://github.com/electronicarts/EABase/archive/521cb053d9320636f53226ffc616216cf532f0ef.tar.gz"
  URL_HASH "SHA3_256=e508facd55e1d94c640a20cd2fa5b59e2e6226de2e6ee4a754a3877637a49801"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME EASTL
#  VERSION 3.21.12
  URL "https://github.com/electronicarts/EASTL/archive/05f4b4aef33f2f3ded08f19fa97f5a27ff35ff9f.tar.gz"
  URL_HASH "SHA3_256=214a22bbc62fe6102a5f5ef119d151eb9caaeb3b1fe9a0b30197e13fbbc04387"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME glm
  VERSION 1.13.0
  URL "https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz"
  URL_HASH "SHA3_256=9384d631dd1fdbf0e48b57c5f1f6868fe3a6da30c3c910a9bfce338a8af683dc"
)

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
add_subdirectory(modules/spatial)


add_executable(main_3 main3.cpp)
target_link_libraries(main_3 PRIVATE
  engine::window
  engine::space
  engine::spatial
  spdlog::spdlog
  chipmunk_static
  glm::glm
)

add_executable(main_2 main2.cpp
  tmp_stuff/StupidSpatial.cpp
  tmp_stuff/StupidSpatial.hpp)
target_link_libraries(main_2 engine::window engine::space spdlog::spdlog chipmunk_static glm::glm)