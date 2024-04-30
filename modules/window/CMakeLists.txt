
add_library(engine-window
  include/engine/window.hpp
  src/window.cpp
  include/engine/window/event.hpp
  src/window-systems.cpp
  include/engine/window/components.hpp
  include/engine/window/components-sfml.hpp
  src/window-components.cpp
  include/engine/graphics.hpp
  src/graphics.cpp
  src/graphics-components.cpp
  src/graphics-components-private.hpp
  src/graphics-systems.cpp
  include/engine/graphics/predefined-colors.hpp
  include/engine/graphics/components.hpp
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