#include <flecs.h>
#include <spdlog/spdlog.h>
#include <engine/window/components.hpp>
#include <engine/window/components-sfml.hpp>

namespace engine::window {

  static bool check_window(const flecs::world& world, SFML_RenderWindow* window) {
    bool exit = false;

    // suppress if we already in exit progress
    if (world.should_quit()) {
      return exit;
    }

    if (!window->window) {
      SPDLOG_CRITICAL("SFML_RenderWindow::window is nullptr. Shutdown");
      exit = true;
    } else if (!window->window->isOpen()) {
      SPDLOG_CRITICAL("SFML_RenderWindow::window closed. Shutdown");
      exit = true;
    }
    if (exit) {
      world.remove<SFML_RenderWindow>();
      world.quit();
    }
    return !exit;
  }

  static void SFML_PollEvents(flecs::iter it, SFML_RenderWindow* window) {
    if (!check_window(it.world(), window)) {
      return;
    }

    sf::Event event;
    while(window->window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->window->close();
      }
    }
  }

  static void SFML_Clear(flecs::iter it, SFML_RenderWindow* window) {
    if (!check_window(it.world(), window)) {
      return;
    }
    window->window->clear();
  }

  static void SFML_Display(flecs::iter it, SFML_RenderWindow* window) {
    if (!check_window(it.world(), window)) {
      return;
    }
    window->window->display();
  }

  void init_window_systems(flecs::world& world) {
    [[maybe_unused]] auto _ = world.scope("systems");

    world.system<SFML_RenderWindow>("SFML_PollEvents")
      .kind<phases::EventPoll>()
      .arg(1).singleton()
      .iter(SFML_PollEvents);

    world.system<SFML_RenderWindow>("SFML_Clear")
      .kind<phases::SFML_WindowClear>()
      .arg(1).singleton()
      .iter(SFML_Clear);

    world.system<SFML_RenderWindow>("SFML_Display")
      .kind<phases::SFML_WindowDisplay>()
      .arg(1).singleton()
      .iter(SFML_Display);
  }

}