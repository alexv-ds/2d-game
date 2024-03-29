#include <type_traits>
#include <random>
#include <flecs.h>
#include <EASTL/algorithm.h>
#include <engine/window/components-sfml.hpp>
#include <engine/graphics.hpp>
#include <engine/space.hpp>
#include "graphics-components-private.hpp"

#include <spdlog/spdlog.h>

namespace engine::graphics {

  static void DrawPrepare(flecs::iter, window::SFML_RenderWindow* render) {
    if (!render->window || !render->window->isOpen()) {
      return;
    }

    auto window_size = render->window->getSize();
    float aspect_ratio = float(window_size.x) / float(window_size.y);
    render->window->setView(
      sf::View({0.0f, 0.0f}, {render->cells_x, -render->cells_x / aspect_ratio})
    );
  }

  static void UpdateVertexesPositionColorAlpha_V2(flecs::iter it,
                                                  const Color* color /* instanced */,
                                                  const Alpha* alpha /* instanced, optional */,
                                                  SFML_Quad* quad /* self */,
                                                  const space::Transform* transform /* self */) {
    static_assert(decltype(SFML_Quad::vertexes)::count == 6);

    for (auto i : it) {
      quad[i].vertexes[0] = {
        .position = {-0.5f, 0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
      quad[i].vertexes[1] = {
        .position = {-0.5f, -0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
      quad[i].vertexes[2] = {
        .position = {0.5f, -0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
      quad[i].vertexes[3] = {
        .position = {-0.5f, 0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
      quad[i].vertexes[4] = {
        .position = {0.5f, -0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
      quad[i].vertexes[5] = {
        .position = {0.5f, 0.5f},
        .color = sf::Color::White,
        .texCoords = {}
      };
    }

    // region Color
    if (it.is_self(1)) {
      for (auto i: it) {
        const sf::Color sf_color(
          static_cast<std::uint8_t>(
            eastl::clamp(static_cast<std::uint32_t>(color[i].r * 255), std::uint32_t{0}, std::uint32_t{255})
          ),
          static_cast<std::uint8_t>(
            eastl::clamp(static_cast<std::uint32_t>(color[i].g * 255), std::uint32_t{0}, std::uint32_t{255})
          ),
          static_cast<std::uint8_t>(
            eastl::clamp(static_cast<std::uint32_t>(color[i].b * 255), std::uint32_t{0}, std::uint32_t{255})
          )
        );

        quad[i].vertexes[0].color = sf_color;
        quad[i].vertexes[1].color = sf_color;
        quad[i].vertexes[2].color = sf_color;
        quad[i].vertexes[3].color = sf_color;
        quad[i].vertexes[4].color = sf_color;
        quad[i].vertexes[5].color = sf_color;
      }
    } else {
      const sf::Color sf_color(
        static_cast<std::uint8_t>(
          eastl::clamp(static_cast<std::uint32_t>(color->r * 255), std::uint32_t{0}, std::uint32_t{255})
        ),
        static_cast<std::uint8_t>(
          eastl::clamp(static_cast<std::uint32_t>(color->g * 255), std::uint32_t{0}, std::uint32_t{255})
        ),
        static_cast<std::uint8_t>(
          eastl::clamp(static_cast<std::uint32_t>(color->b * 255), std::uint32_t{0}, std::uint32_t{255})
        )
      );

      for (auto i: it) {
        quad[i].vertexes[0].color = sf_color;
        quad[i].vertexes[1].color = sf_color;
        quad[i].vertexes[2].color = sf_color;
        quad[i].vertexes[3].color = sf_color;
        quad[i].vertexes[4].color = sf_color;
        quad[i].vertexes[5].color = sf_color;
      }
    }
    // endregion

    // region Alpha
    if (alpha) {
      if (it.is_self(2)) {
        for (auto i: it) {
          const std::uint8_t a = eastl::clamp(
            static_cast<std::uint8_t>(alpha[i].a * 255),
            std::uint8_t{0},
            std::uint8_t{255}
          );
          quad[i].vertexes[0].color.a = a;
          quad[i].vertexes[1].color.a = a;
          quad[i].vertexes[2].color.a = a;
          quad[i].vertexes[3].color.a = a;
          quad[i].vertexes[4].color.a = a;
          quad[i].vertexes[5].color.a = a;
        }
      } else {
        const std::uint8_t a = eastl::clamp(
          static_cast<std::uint8_t>(alpha->a * 255),
          std::uint8_t{0},
          std::uint8_t{255}
        );

        for (auto i: it) {
          quad[i].vertexes[0].color.a = a;
          quad[i].vertexes[1].color.a = a;
          quad[i].vertexes[2].color.a = a;
          quad[i].vertexes[3].color.a = a;
          quad[i].vertexes[4].color.a = a;
          quad[i].vertexes[5].color.a = a;
        }
      }
    }
    // endregion

    // apply transform
    for (auto i: it) {
      for (sf::Vertex& vertex: quad[i].vertexes) {
        const glm::vec3 new_position = transform[i] * glm::vec3(vertex.position.x, vertex.position.y, 1.0f);
        vertex.position = {new_position.x, new_position.y};
      }
    }
  }

  static void Draw(flecs::iter it,
                   window::SFML_RenderWindow* render /* singleton */,
                   const SFML_Quad* quad /* self */,
                   const SFML_RenderStates* states /* instanced */,
                   const Layer* /* instanced */) {
    constexpr std::size_t quad_vert_count = decltype(SFML_Quad::vertexes)::count;
    static_assert(std::is_same_v<decltype(SFML_Quad::vertexes), eastl::array<sf::Vertex, quad_vert_count>>);
    // Checking that SFML_Quad has only a member with an array of vertices
    static_assert(sizeof(SFML_Quad) == sizeof(eastl::array<sf::Vertex, quad_vert_count>));

    if (!render->window || !render->window->isOpen()) {
      return;
    }

    sf::RenderTarget& render_target = *render->window;

    if (it.is_self(3)) {
      for (auto i: it) {
        render_target.draw(
          quad[i].vertexes.data(),
          quad_vert_count,
          sf::PrimitiveType::Triangles,
          states[i].states
        );
      }
    } else {
      render_target.draw(
        reinterpret_cast<const sf::Vertex*>(quad),
        it.count() * quad_vert_count,
        sf::PrimitiveType::Triangles,
        states->states
      );
    }
  }

  static void FixBlinking(flecs::iter it,
                          const FixEqualLayerBlinking* /* self */,
                          Layer* layer /* instanced */) {

    // if exists and self component
    // for instanced not needed
    if (layer && it.is_self(2)) {
      thread_local std::uniform_real_distribution<float> distribution(-0.01, 0.01);
      thread_local std::default_random_engine random_engine = []() {
        std::random_device rd;
        return std::default_random_engine(rd());
      }();

      for (auto i: it) {
        layer[i].z += distribution(random_engine);
      }
    }

    for (auto i: it) {
      it.entity(i).remove<FixEqualLayerBlinking>();
    }
  }

  static inline int layer_compare(flecs::entity_t e1, const Layer* l1, flecs::entity_t e2, const Layer* l2) {
    if (l1->z > l2->z) {
      return 1;
    } else if (l1->z < l2->z) {
      return -1;
    } else {
      return 0;
    }
  }

  void init_graphics_systems(flecs::world & world) {
    [[maybe_unused]] auto _ = world.scope("systems");

    world.system<const Color, const Alpha, SFML_Quad, const space::Transform>(
        "UpdateVertexesPositionColorAlpha_V2")
      .instanced()
      .kind(flecs::PostUpdate)
      .arg(2).optional()
      .arg(3).self()
      .arg(4).self()
      .iter(UpdateVertexesPositionColorAlpha_V2);

    world.system<window::SFML_RenderWindow>("DrawPrepare")
      .kind<window::phases::SFML_WindowDisplayPre>()
      .arg(1).singleton()
      .iter(DrawPrepare);

    world.system<window::SFML_RenderWindow, const SFML_Quad, const SFML_RenderStates, const Layer>("Draw")
      .instanced()
      .kind<window::phases::SFML_WindowDisplayPre>()
      .arg(1).singleton()
      .arg(2).self()
      .order_by<Layer>(layer_compare)
      .iter(Draw);

    world.system<const FixEqualLayerBlinking, Layer>("FixEqualLayerBlinking")
      .instanced()
      .arg(1).self()
      .iter(FixBlinking);

  }

}