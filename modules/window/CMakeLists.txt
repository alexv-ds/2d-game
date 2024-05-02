
add_library(engine-window)
add_library(engine::window ALIAS engine-window)
target_include_directories(engine-window PUBLIC include)

target_link_libraries(engine-window PUBLIC
  sfml-graphics
  flecs::flecs_static
  EASTL
)
target_link_libraries(engine-window PRIVATE spdlog::spdlog engine::space)

target_sources(engine-window PUBLIC FILE_SET CXX_MODULES FILES
  engine.window.cppm
  window/engine.window.components.cppm
  engine.window.sfml.cppm
  window/engine.window.components_impl.cppm
  window/engine.window.systems_impl.cppm
  
  engine.graphics.cppm
  engine.graphics.colors.cppm
  graphics/engine.graphics.systems.cppm
  graphics/engine.graphics.components.cppm
  graphics/engine.graphics.components_internal.cppm
  graphics/engine.graphics.components_impl.cppm
)