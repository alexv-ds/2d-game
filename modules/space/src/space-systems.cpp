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

  static void UpdateTransformKEKS(flecs::iter& it,
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
      .without<Static>()
      .iter(UpdateScale);

    world.system<const Scale, Scale, const Scale>("UpdateScaleStatic")
      .kind(flecs::PostUpdate)
      .arg(2).second<Global>()
      .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
      .with<Static>()
      .with<Recalculate>()
      .iter(UpdateScale);


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
//      .without<Static>()
      .iter(UpdateTransformKEKS);


  }
}