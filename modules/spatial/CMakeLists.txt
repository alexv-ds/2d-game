
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
  spatial/engine.spatial.xy_iterator.cppm
)