
add_library(engine-space)
add_library(engine::space ALIAS engine-space)
target_include_directories(engine-space PUBLIC include)

target_link_libraries(engine-space PUBLIC flecs::flecs_static glm::glm)
target_link_libraries(engine-space PRIVATE spdlog::spdlog EASTL)


target_sources(engine-space PUBLIC FILE_SET CXX_MODULES FILES
  engine.space.cppm
  space/engine.space.components.cppm
  space/engine.space.components_impl.cppm
  space/engine.space.systems.cppm
)