#include "TheRayTracerChallenge/chapter7/chapter7.h"

// Method to intersect the ray and the world
std::vector<struct Intersection*> Intersect(struct Ray ray,
                                            struct World world) {
  std::vector<struct Intersection*> intersections;
  for (int i = 0; i < world.objects.size(); i++) {
    std::vector<struct Intersection*> intersection =
        Intersect(ray, world.objects[i].sphere);
    for (int j = 0; j < intersection.size(); j++) {
      intersections.push_back(intersection[j]);
    }
  }
  return intersections;
}

// Preapare computation
struct Comps PrepareComputations(struct Intersection intersection,
                                 struct Ray ray) {
  struct Comps comps;
  comps.t = intersection.t;
  // Intersection Object
  comps.object = intersection.object;

  comps.point = Position(ray, comps.t);
  comps.eyev = -ray.direction;
  comps.normalv = NormalAt(comps.object.sphere, comps.point);

  if (comps.normalv.dot(comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }
  return comps;
}

// Shade hit function
Eigen::Vector3f ShadeHit(struct World world, struct Comps comps) {
  return Lighting(comps.object.sphere.material, world.light, comps.point,
                  comps.eyev, comps.normalv);
}