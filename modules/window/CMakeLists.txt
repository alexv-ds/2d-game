
add_library(engine-window
  include/engine/window.hpp
  src/window.cpp
  include/engine/window/event.hpp
)
add_library(engine::window ALIAS engine-window)
target_include_directories(engine-window PUBLIC include)

CPMGetPackage(SFML)
CPMGetPackage(flecs)
CPMGetPackage(cpp-fast-pimpl)
CPMGetPackage(spdlog)

target_link_libraries(engine-window PUBLIC
  sfml-graphics
  flecs::flecs_static
  fpimpl::fpimpl
  EASTL::EASTL
)
target_link_libraries(engine-window PRIVATE spdlog::spdlog)