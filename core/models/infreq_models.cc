#include "core/models/infreq_models.h"

struct Projectile Tick(struct Environment env, struct Projectile pro) {
  struct Tuple4 position = add(pro.position, pro.velocity);
  struct Tuple4 velocity = add(pro.velocity, env.gravity);
  velocity = add(velocity, env.wind);
  return Projectile(position, velocity);
}