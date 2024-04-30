
add_library(engine-space
  include/engine/space.hpp
  src/space.cpp
  src/space-components.cpp
  src/space-systems.cpp
  src/SpatialHash.hpp
  src/SpatialHash.cpp
)
add_library(engine::space ALIAS engine-space)
target_include_directories(engine-space PUBLIC include)

target_link_libraries(engine-space PUBLIC flecs::flecs_static glm::glm)
target_link_libraries(engine-space PRIVATE spdlog::spdlog EASTL)