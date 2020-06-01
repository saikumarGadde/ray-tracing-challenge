#include "core/chapter1/chapter1.h"
#include <assert.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Tuple4 Point(float x, float y, float z) {
  std::cout << " x: " << x << " y : " << y << " z: " << z << std::endl;
  Tuple4 point;
  point.x = x;
  point.y = y;
  point.z = z;
  point.w = 1.0;
  return point;
}

struct Tuple4 Vector(float x, float y, float z) {
  Tuple4 vector;
  vector.x = x;
  vector.y = y;
  vector.z = z;
  vector.w = 0.0;
  return vector;
}

bool equal(float x, float y) {
  const float epsilon = 0.00001;
  if (abs(x - y) < epsilon) {
    return true;
  }
  return false;
}

struct Tuple4 add(Tuple4 a, Tuple4 b) {
  struct Tuple4 sum;
  sum.x = a.x + b.x;
  sum.y = a.y + b.y;
  sum.z = a.z + b.z;
  sum.w = a.w + b.w;
  if (sum.w > 1) {
    std::cout << "They should be a point and a vector or a vector and vector"
              << std::endl;
  }
  return sum;
}

struct Tuple4 subtract(struct Tuple4 a, struct Tuple4 b) {
  struct Tuple4 difference;
  difference.x = a.x - b.x;
  difference.y = a.y - b.y;
  difference.z = a.z - b.z;
  difference.w = a.w - b.w;
  if (difference.w < 0) {
    std::cout << "a has to be a point and b can be a point or a vector and the "
                 "computation is a - b"
              << std::endl;
  }
  return difference;
}

struct Tuple4 Negate(struct Tuple4 vector) {
  struct Tuple4 opposite;
  opposite.x = -vector.x;
  opposite.y = -vector.y;
  opposite.z = -vector.z;
  opposite.w = vector.w;
  return opposite;
}

struct Tuple4 Multiply(struct Tuple4 vector, float scalar_value) {
  struct Tuple4 multiplied_value;
  multiplied_value.x = vector.x * scalar_value;
  multiplied_value.y = vector.y * scalar_value;
  multiplied_value.z = vector.z * scalar_value;
  multiplied_value.w = vector.w;
  return multiplied_value;
}

struct Tuple4 Division(struct Tuple4 vector, float scalar_value) {
  struct Tuple4 divided_value;
  divided_value.x = vector.x / scalar_value;
  divided_value.y = vector.y / scalar_value;
  divided_value.z = vector.z / scalar_value;
  divided_value.w = vector.w;
  return divided_value;
}

float Magnitude(struct Tuple4 vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

struct Tuple4 Normalization(struct Tuple4 vector) {
  assert(vector.w == 0);
  float vector_magnitude = Magnitude(vector);
  struct Tuple4 normalized_vector;
  normalized_vector.x = vector.x / vector_magnitude;
  normalized_vector.y = vector.y / vector_magnitude;
  normalized_vector.z = vector.z / vector_magnitude;
  normalized_vector.w = vector.w;
  return normalized_vector;
}

float DotProduct(Tuple4 v1, Tuple4 v2) {
  if (v1.w == 0 && v2.w == 0) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  } else {
    std::cout << "Both arguments should be vectors" << std::endl;
  }
}

struct Tuple4 CrossProduct(struct Tuple4 a, struct Tuple4 b) {
  struct Tuple4 cross_product;
  cross_product.x = a.y * b.z - a.z * b.y;
  cross_product.y = a.z * b.x - a.x * b.z;
  cross_product.z = a.x * b.y - a.y * b.x;
  cross_product.w = 0;
  return cross_product;
}

struct Projectile Tick(struct Environment env, struct Projectile pro) {
  struct Tuple4 position = add(pro.position, pro.velocity);
  struct Tuple4 velocity = add(pro.velocity, env.gravity);
  velocity = add(velocity, env.wind);
  return Projectile(position, velocity);
}