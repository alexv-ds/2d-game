#include <algorithm>
#include <SFML/Graphics.hpp>
#include <EASTL/array.h>
#include <EASTL/vector.h>
#include <EASTL/algorithm.h>
#include <engine/space.hpp>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/graphics.hpp>

#include <spdlog/spdlog.h>

namespace engine::graphics {

  struct DrawBuffer {
    struct Quad {
      eastl::array<sf::Vertex, 6> vertexes = {};
      const sf::RenderStates* states = nullptr;
      float layer = 0.0f;
    };

    eastl::vector<Quad> render_buffer;
  };

  static void draw_rect(sf::RenderTarget& target,
                        const space::Position& pos,
                        const space::Rotation& rotation,
                        const space::Scale& scale,
                        const space::Size& size,
                        const Color& color) {


    sf::Color sf_color(
      std::clamp(static_cast<std::uint8_t>(color.r * 255), std::uint8_t{0}, std::uint8_t{255}),
      std::clamp(static_cast<std::uint8_t>(color.g * 255), std::uint8_t{0}, std::uint8_t{255}),
      std::clamp(static_cast<std::uint8_t>(color.b * 255), std::uint8_t{0}, std::uint8_t{255})
    );

    eastl::array<sf::Vertex, 4> vertexes = {
      {
        {
          .position = {-size.x * 0.5f, -size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {size.x * 0.5f, -size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {size.x * 0.5f, size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {-size.x * 0.5f, size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
      }
    };

    sf::Transform transform;
    transform.translate({pos.x, pos.y});
    transform.scale({scale.x, scale.y});
    transform.rotate(sf::radians(rotation.rad));
    for (sf::Vertex& vertex : vertexes) {
      vertex.position = transform.transformPoint(vertex.position);
    }

    target.draw(vertexes.data(), vertexes.size(), sf::PrimitiveType::TriangleFan);

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

    auto window_size = render->window->getSize();
    float aspect_ratio = float(window_size.x) / float(window_size.y);
    render->window->setView(
      sf::View({0.0f, 0.0f}, {10, -10 / aspect_ratio})
    );

    for (auto i: it) {
      draw_rect(
        *render->window,
        position[i],
        rotation ? rotation[i] : space::Rotation{},
        scale ? scale[i] : space::Scale{},
        size[i],
        color[i]
      );
    }
  }

  static void DrawPrepare(flecs::iter, DrawBuffer* buf, window::SFML_RenderWindow* render) {
    buf->render_buffer.clear();

    if (!render->window || !render->window->isOpen()) {
      return;
    }

    auto window_size = render->window->getSize();
    float aspect_ratio = float(window_size.x) / float(window_size.y);
    render->window->setView(
      sf::View({0.0f, 0.0f}, {10, -10 / aspect_ratio})
    );
  }

  static eastl::array<sf::Vertex, 6> create_quad(const space::Position& position,
                                                 const space::Rotation& rotation,
                                                 const space::Scale& scale,
                                                 const space::Size& size,
                                                 const Color& color) {
    sf::Color sf_color(
      std::clamp(static_cast<std::uint8_t>(color.r * 255), std::uint8_t{0}, std::uint8_t{255}),
      std::clamp(static_cast<std::uint8_t>(color.g * 255), std::uint8_t{0}, std::uint8_t{255}),
      std::clamp(static_cast<std::uint8_t>(color.b * 255), std::uint8_t{0}, std::uint8_t{255})
    );

    return {
      {
        {
          .position = {-size.x * 0.5f, size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {-size.x * 0.5f, -size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {size.x * 0.5f, -size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {-size.x * 0.5f, size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {size.x * 0.5f, -size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        },
        {
          .position = {size.x * 0.5f, size.y * 0.5f},
          .color = sf_color,
          .texCoords = {}
        }
      }
    };
  }

  static void FillDrawBuffer(flecs::iter it,
                             window::SFML_RenderWindow* render,
                             DrawBuffer* buf,
                             const space::Position* position,
                             const space::Rotation* rotation,
                             const space::Scale* scale,
                             const space::Size* size,
                             const Color* color) {
    if (!render->window || !render->window->isOpen()) {
      return;
    }

    for (auto i: it) {
      buf->render_buffer.push_back(
        {
          .vertexes = create_quad(
            position[i],
            rotation ? rotation[i] : space::Rotation{},
            scale ? scale[i] : space::Scale{},
            size[i],
            color[i]
          ),
          .states = nullptr,
          .layer = 0.0f,
        }
      );
    }

  }

  static void RenderBuffer(flecs::iter, window::SFML_RenderWindow* render, DrawBuffer* buf) {
    if (!render->window || !render->window->isOpen()) {
      return;
    }

    static eastl::vector<sf::Vertex> vetrs;

    vetrs.clear();

    for (auto& quad : buf->render_buffer) {
      eastl::copy(quad.vertexes.begin(), quad.vertexes.end(), eastl::back_insert_iterator(vetrs));
    }

    SPDLOG_INFO(vetrs.size());

    render->window->draw(vetrs.data(), vetrs.size(), sf::PrimitiveType::Triangles);

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

  //private components
  {
    auto _ = world.scope("private");
    world.component<DrawBuffer>();
    world.add<DrawBuffer>();
  }

  {
    auto _ = world.scope("systems");

    world.system<
        window::SFML_RenderWindow,
        const space::Position,
        const space::Rotation,
        const space::Scale,
        const space::Size,
        const Color>("Draw")
      .kind<window::phases::SFML_WindowClear>()
      .arg(1).singleton()
      .arg(2).second<space::Global>()
      .arg(3).optional().second<space::Global>()
      .arg(4).optional().second<space::Global>()
      .iter(Draw)
      .add(flecs::Disabled);

    world.system<DrawBuffer>("DrawPrepare")
      .kind<window::phases::SFML_WindowClear>()
      .arg(1).singleton()
      .iter([](flecs::iter, DrawBuffer* buf) { buf->render_buffer.clear(); });

    world.system<
        window::SFML_RenderWindow,
        DrawBuffer,
        const space::Position,
        const space::Rotation,
        const space::Scale,
        const space::Size,
        const Color>("FillDrawBuffer")
      .kind<window::phases::SFML_WindowClear>()
      .arg(1).singleton()
      .arg(2).singleton()
      .arg(3).second<space::Global>()
      .arg(4).optional().second<space::Global>()
      .arg(5).optional().second<space::Global>()
      .iter(FillDrawBuffer);

    world.system<window::SFML_RenderWindow, DrawBuffer>("RenderBuffer")
      .kind<window::phases::SFML_WindowClear>()
      .arg(1).singleton()
      .arg(2).singleton()
      .iter(RenderBuffer);
  }
}