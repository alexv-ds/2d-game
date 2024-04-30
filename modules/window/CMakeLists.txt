
add_library(engine-window
  include/engine/window.hpp
  src/window.cpp
  include/engine/window/event.hpp
  src/window-systems.cpp
  include/engine/window/components.hpp
  include/engine/window/components-sfml.hpp
  src/window-components.cpp
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
  window.cppm
  graphics.cppm
  graphics.colors.cppm
  graphics.systems.cppm
  graphics.components.cppm
  graphics.components.internal.cppm
)