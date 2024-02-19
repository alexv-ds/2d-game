#pragma once

#include <flecs.h>
#include <fpimpl.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <EASTL/shared_ptr.h>
#include <EASTL/fixed_vector.h>
#include "window/event.hpp"

namespace engine {

  class Window {
  public:
    explicit Window(flecs::world&);
    ~Window();

    Window(Window&&) = default;
    Window& operator= (Window&&) = default;

    eastl::shared_ptr<sf::RenderTarget> render_target();
    [[nodiscard]] const eastl::fixed_vector<window::Event, 10, false>& events() const noexcept;

  private:
    struct Impl;
    fpimpl<Impl, 72, 8> impl;
  };

  namespace window {
    struct Opened {};
    struct Focused {};
  } // namespace window

  namespace window::phases {
    struct EventPollPre {};
    struct EventPoll {};
    struct WindowClearPre {};
    struct WindowClear {};
    struct WindowDisplayPre {};
    struct WindowDisplay {};
  } // namespace phases
} // namespace engine
