
add_library(engine-spatial)
add_library(engine::spatial ALIAS engine-spatial)

target_link_libraries(engine-spatial PUBLIC
  engine::space
  flecs::flecs_static
)
target_link_libraries(engine-spatial PRIVATE spdlog::spdlog engine::space)

target_sources(engine-spatial PUBLIC FILE_SET CXX_MODULES FILES
  engine.spatial.cppm
  spatial/engine.spatial.components.cppm
  engine.spatial.xy_iterator.cppm
)

if (BUILD_TESTING)
  add_executable(test-engine-spatial
    test/xy_iterator.test.cpp
  )
  target_link_libraries(test-engine-spatial PRIVATE Catch2::Catch2WithMain engine::spatial)
  catch_discover_tests(test-engine-spatial)
endif ()