#include <SFML/Graphics.hpp>
#include <engine/window.hpp>

static void compile_check(flecs::world& world) {
  world.import<engine::Window>();
}

namespace engine {

  struct Window::Impl {
    eastl::shared_ptr<sf::RenderWindow> window;
    eastl::fixed_vector<window::Event, 10, false> events;
  };

  Window::Window(flecs::world& world) {
    world.module<Window>();
  }

  Window::~Window() = default;


  eastl::shared_ptr<sf::RenderTarget> Window::render_target() {
    return nullptr;
  }

  const eastl::fixed_vector<window::Event, 10, false>& Window::events() const noexcept {
    return impl->events;
  }
}

