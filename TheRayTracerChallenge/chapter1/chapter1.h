
#pragma once

#include <math.h>
#include "core/protos/entities_3d.h"

// Point function to create a point
struct Tuple4 Point(float x, float y, float z);

// Vector function to create a vector
struct Tuple4 Vector(float x, float y, float z);

// Compare two floating point numbers
bool equal(float x, float y);

// Add two tuples
struct Tuple4 add(struct Tuple4 a, struct Tuple4 b);

// Subtract two tuples
// a has to be a point and b can be a point or a vector
struct Tuple4 subtract(struct Tuple4 a, struct Tuple4 b);

// Negating a vector
struct Tuple4 Negate(struct Tuple4 vector);

// Scalar multiplication
struct Tuple4 Multiply(struct Tuple4 vector, float scalar_value);

// Scalar division of a vector
struct Tuple4 Division(struct Tuple4 vector, float scalar_value);

// Magnitude of a vector
float Magnitude(struct Tuple4 vector);

// Normalization of the given vector
struct Tuple4 Normalization(struct Tuple4 vector);

// Dot product of two vectors
float DotProduct(Tuple4 v1, Tuple4 v2);

// Cross product of two vectors
struct Tuple4 CrossProduct(struct Tuple4 v1, struct Tuple4 v2);

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