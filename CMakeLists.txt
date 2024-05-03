cmake_minimum_required(VERSION 3.29)

cmake_policy(SET CMP0069 NEW)

project(2d-game VERSION 0.0.1 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ENGINE_BUILD_TESTING OFF CACHE BOOL "Build Engine Tests")

if (ENGINE_BUILD_TESTING)
  include(CTest)
endif ()

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  EASTL_DEBUGPARAMS_LEVEL=2
  EASTL_NAME_ENABLED
  GLM_ENABLE_EXPERIMENTAL
)

include(cmake/get_cpm.cmake)
include(cmake/cpm-dependencies.cmake)

if (ENGINE_BUILD_TESTING)
  include(Catch)
endif ()

add_subdirectory(modules/space)
add_subdirectory(modules/window)
add_subdirectory(modules/spatial)

add_executable(main_3 main3.cpp)
target_link_libraries(main_3 PRIVATE
  engine::window
  engine::space
  engine::spatial
  spdlog::spdlog
  glm::glm
)

add_executable(main_2 main2.cpp)
target_link_libraries(main_2 engine::window engine::space spdlog::spdlog glm::glm)