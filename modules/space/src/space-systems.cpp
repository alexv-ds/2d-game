#include <flecs.h>
#include <engine/space.hpp>

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

  static void UpdateRotation(flecs::iter& it, const Rotation* local, Rotation* global, const Rotation* parent) {}

  static void UpdateScale(flecs::iter& it, const Scale* local, Scale* global, const Scale* parent) {}

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
  }
}