#include <type_traits>
#include <cstring>
#include <flecs.h>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/quaternion.hpp>
#include <engine/space.hpp>

#include <spdlog/spdlog.h>

namespace engine::space {
  static void UpdatePosition(flecs::iter& it, const Position* local, Position* global, const Position* parent) {
    if (parent) {
      for (auto i: it) {
        global[i].x = local[i].x + parent[i].x;
        global[i].y = local[i].y + parent[i].y;
      }
    } else {
      for (auto i: it) {
        global[i].x = local[i].x;
        global[i].y = local[i].y;
      }
    }
  }

  static void UpdateRotation(flecs::iter& it, const Rotation* local, Rotation* global, const Rotation* parent) {
    if (parent) {
      for (auto i: it) {
        global[i].rad = local[i].rad + parent[i].rad;
      }
    } else {
      for (auto i: it) {
        global[i].rad = local[i].rad;
      }
    }
  }

  static void UpdateScale(flecs::iter& it, const Scale* local, Scale* global, const Scale* parent) {
    if (parent && !it.is_set(4)) {
      for (auto i: it) {
        global[i].x = local[i].x * parent[i].x;
        global[i].y = local[i].y * parent[i].y;
      }
    } else {
      for (auto i: it) {
        global[i].x = local[i].x;
        global[i].y = local[i].y;
      }
    }
  }

  static void UpdateTransform(flecs::iter& it,
                              Transform* transform /* self */,
                              const space::Position* position /* self */,
                              const space::Rotation* rotation /* instanced, optional */,
                              const space::Scale* scale /* instanced, optional */) {
    // Translate
    for (auto i: it) {
      transform[i] = glm::translate(glm::mat3(1), {position[i].x, position[i].y});
    }

    // region Scale
    if (scale) {
      if (it.is_self(4)) {
        for (auto i: it) {
          transform[i] = glm::scale(transform[i], {scale[i].x, scale[i].y});
        }
      } else {
        for (auto i: it) {
          transform[i] = glm::scale(transform[i], {scale->x, scale->y});
        }
      }
    }
    // endregion

    // region Rotation
    if (rotation) {
      if (it.is_self(3)) {
        for (auto i: it) {
          transform[i] = glm::rotate(transform[i], rotation[i].rad);
        }
      } else {
        for (auto i: it) {
          transform[i] = glm::rotate(transform[i], rotation->rad);
        }
      }
    }
    // endregion
  }

//Описывает неповернутый прямоугольник вокруг повернутого прямоугольника
  inline glm::vec2 describe_rectangle(glm::vec2 size, float angle) {
    float abs_sin_angle = glm::abs(glm::sin(angle));
    float abs_cos_angle = glm::abs(glm::cos(angle));
    return {
      size.x * abs_cos_angle + size.y * abs_sin_angle,
      size.x * abs_sin_angle + size.y * abs_cos_angle
    };
  }

  static void UpdateBBox(flecs::iter& it,
                  BBox* bbox /* self */,
                  const Scale* scale /* instanced, optional */,
                  const Rotation* rotation /* instanced, optional */) {

    if (scale) {
      if (it.is_self(2)) {
        static_assert(std::is_trivially_copyable_v<Scale>);
        static_assert(std::is_trivially_copyable_v<BBox>);
        static_assert(std::is_base_of_v<glm::vec2, Scale>);
        static_assert(std::is_base_of_v<glm::vec2, BBox>);
        static_assert(sizeof(BBox) == sizeof(Scale));
        std::memcpy(bbox, scale, sizeof(BBox) * it.count());
      } else {
        for (auto i: it) {
          bbox[i] = *scale;
        }
      }
    } else {
      for (auto i: it) {
        bbox[i] = {1.0f, 1.0f};
      }
    }

    if (rotation) {
      if (it.is_self(3)) {
        for (auto i: it) {
          const float abs_sin_angle = glm::abs(glm::sin(rotation[i]));
          const float abs_cos_angle = glm::abs(glm::cos(rotation[i]));
          bbox[i] = glm::vec2(
            bbox[i].x * abs_cos_angle + bbox[i].y * abs_sin_angle,
            bbox[i].x * abs_sin_angle + bbox[i].y * abs_cos_angle
          );
        }
      } else {
        const float abs_sin_angle = glm::abs(glm::sin(*rotation));
        const float abs_cos_angle = glm::abs(glm::cos(*rotation));
        for (auto i : it) {
          bbox[i] = glm::vec2(
            bbox[i].x * abs_cos_angle + bbox[i].y * abs_sin_angle,
            bbox[i].x * abs_sin_angle + bbox[i].y * abs_cos_angle
          );
        }
      }
    }

  }

  void init_space_systems(flecs::world & world) {
    [[maybe_unused]] auto _ = world.scope("systems");

    // Position
    world.system<const Position, Position, const Position>("UpdatePosition")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .without<Static>()
      .iter(UpdatePosition);

    world.system<const Position, Position, const Position>("UpdatePositionStatic")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdatePosition);

    // Rotation
    world.system<const Rotation, Rotation, const Rotation>("UpdateRotation")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .without<Static>()
      .iter(UpdateRotation);

    world.system<const Rotation, Rotation, const Rotation>("UpdateRotationStatic")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdateRotation);

    // Scale
    world.system<const Scale, Scale, const Scale>("UpdateScale")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .with<IgnoreParentScale>().optional()
      .without<Static>()
      .iter(UpdateScale);

    world.system<const Scale, Scale, const Scale>("UpdateScaleStatic")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .with<IgnoreParentScale>().optional()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdateScale);

    // UpdateBBox
    world.system<BBox, const Scale, const Rotation>("UpdateBBox")
      .instanced()
      .kind(flecs::PostUpdate)
      .arg(1).self()
      .arg(2).optional()
      .arg(3).optional()
      .without<Static>()
      .iter(UpdateBBox);

    world.system<BBox, const Scale, const Rotation>("UpdateBBoxStatic")
      .instanced()
      .kind(flecs::PostUpdate)
      .arg(1).self()
      .arg(2).optional().second<space::Global>()
      .arg(3).optional().second<space::Global>()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdateBBox);


    world.system<
        Transform,
        const space::Position,
        const space::Rotation,
        const space::Scale>("UpdateTransform")
      .instanced()
      .kind(flecs::PostUpdate)
      .arg(1).self()
      .arg(2).self().second<space::Global>()
      .arg(3).optional().second<space::Global>()
      .arg(4).optional().second<space::Global>()
      .without<Static>()
      .iter(UpdateTransform);

    world.system<
        Transform,
        const space::Position,
        const space::Rotation,
        const space::Scale>("UpdateTransformStatic")
      .instanced()
      .kind(flecs::PostUpdate)
      .arg(1).self()
      .arg(2).self().second<space::Global>()
      .arg(3).optional().second<space::Global>()
      .arg(4).optional().second<space::Global>()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdateTransform);
  }
}