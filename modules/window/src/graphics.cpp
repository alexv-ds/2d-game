#include <SFML/Graphics.hpp>
#include <engine/space.hpp>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/graphics.hpp>

namespace engine::graphics {

  static void draw_rect(sf::RenderTarget& target,
                        const space::Position& pos,
                        const space::Rotation& rotation,
                        const space::Scale& scale,
                        const space::Size& size,
                        const Color& color) {

  }


  static void Draw(flecs::iter it,
                   window::SFML_RenderWindow* render,
                   const space::Position* position,
                   const space::Rotation* rotation,
                   const space::Scale* scale,
                   const space::Size* size,
                   const Color* color) {
    if (!render->window || !render->window->isOpen()) {
      return;
    }

    for (auto i: it) {
      draw_rect(
        *render->window,
        position[i],
        rotation ? rotation[i] : space::Rotation{},
        scale ? scale[i] : space::Scale{},
        size ? size[i] : space::Size{},
        color ? color[i] : Color{}
      );
    }


  }

}

engine::Graphics::Graphics(flecs::world& world) {
  world.import<Space>();
  world.import<Window>();
  world.module<Graphics>();

  using namespace graphics;

  world.component<Color>()
    .member<decltype(Color::r)>("r")
    .member<decltype(Color::g)>("g")
    .member<decltype(Color::b)>("b");


  {
    auto _ = world.scope("systems");

    world.system<
        window::SFML_RenderWindow,
        const space::Position,
        const space::Rotation,
        const space::Scale,
        const space::Size,
        const Color>("Draw")
      .arg(1).singleton()
      .arg(2).second<space::Global>()
      .arg(3).optional().second<space::Global>()
      .arg(4).optional().second<space::Global>()
      .arg(5).optional()
      .iter(Draw);
  }
}