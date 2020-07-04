#pragma once
#include <math.h>
#include "core/ops/vector_ops.h"
#include "core/protos/entities_3d.h"

// Projectile
struct Projectile {
  // Constructor
  Projectile(struct Tuple4 position, struct Tuple4 velocity)
      : position(position), velocity(velocity) {}
  // Position is a point
  struct Tuple4 position;
  // Velocity is a vector
  struct Tuple4 velocity;
};

// Environment
struct Environment {
  // Constructor
  Environment(struct Tuple4 gravity, struct Tuple4 wind)
      : gravity(gravity), wind(wind) {}
  // gravity is a vector
  struct Tuple4 gravity;
  // Wind is also a vector
  struct Tuple4 wind;
};

struct Projectile Tick(struct Environment env, struct Projectile pro);