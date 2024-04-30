cmake_minimum_required(VERSION 3.29)

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
  GLM_ENABLE_EXPERIMENTAL
)


include(cmake/get_cpm.cmake)
CPMUsePackageLock(package-lock.cmake)


CPMAddPackage(
  NAME EABase 
  VERSION 2.09.05
  URL "https://github.com/electronicarts/EABase/archive/refs/tags/2.09.05.tar.gz"
  URL_HASH "SHA3_256=6b4d6aabe4a5c08eec09c5b0196582f4fb289dcbc108498eedb00460656c83c0"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME EASTL
  VERSION 3.21.12
  URL "https://github.com/electronicarts/EASTL/archive/refs/tags/3.21.12.tar.gz"
  URL_HASH "SHA3_256=72900db956415acc1e7007defcc1e9c4c0dfbee78be38ce667a1113f602532ea"
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

add_executable(main_1 main.cpp)
target_link_libraries(main_1 engine::window engine::space spdlog::spdlog chipmunk_static glm::glm)

add_executable(main_3 main3.cpp)
target_link_libraries(main_3 engine::window engine::space spdlog::spdlog chipmunk_static glm::glm)

add_executable(main_2 main2.cpp
  tmp_stuff/StupidSpatial.cpp
  tmp_stuff/StupidSpatial.hpp)
target_link_libraries(main_2 engine::window engine::space spdlog::spdlog chipmunk_static glm::glm)