#include <flecs.h>

#include <engine/window/components.hpp>
#include <engine/window/components-sfml.hpp>

namespace engine::window {
  void init_window_components(flecs::world& world) {
    world.component<Opened>();
    world.component<Focused>();
    world.component<SFML_RenderWindow>();
  }

  void init_window_phases(flecs::world& world) {
    [[maybe_unused]] auto _ = world.scope("phases");

    world.entity<phases::EventPollPre>()
      .add(flecs::Phase)
      .depends_on(flecs::OnLoad);

    world.entity<phases::EventPoll>()
      .add(flecs::Phase)
      .depends_on<phases::EventPollPre>();

    world.entity<phases::SFML_WindowClearPre>()
      .add(flecs::Phase)
      .depends_on(flecs::PreStore);

    world.entity<phases::SFML_WindowClear>()
      .add(flecs::Phase)
      .depends_on<phases::SFML_WindowClearPre>();

    world.entity<phases::SFML_WindowDisplayPre>()
      .add(flecs::Phase)
      .depends_on(flecs::PostFrame);

    world.entity<phases::SFML_WindowDisplay>()
      .add(flecs::Phase)
      .depends_on<phases::SFML_WindowDisplayPre>();
  }
}