
add_library(engine-space
  include/engine/space.hpp
  src/space.cpp
  src/space-components.cpp
)
add_library(engine::space ALIAS engine-space)
target_include_directories(engine-space PUBLIC include)

target_link_libraries(engine-space PUBLIC flecs::flecs_static)
target_link_libraries(engine-space PRIVATE spdlog::spdlog)