
add_library(engine-window
#  include/engine/window.hpp
#  src/window.cpp
#  src/graphics.cpp
#  src/graphics-components.cpp
#  src/graphics-systems.cpp
)
add_library(engine::window ALIAS engine-window)
target_include_directories(engine-window PUBLIC include)

CPMGetPackage(SFML)
CPMGetPackage(flecs)
CPMGetPackage(spdlog)

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
)