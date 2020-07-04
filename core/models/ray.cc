#include "core/models/ray.h"

Eigen::Vector4f Ray::Position(const float distance) const {
  return origin_ + (direction_ * distance);
}

void Ray::SetTransform(Eigen::Matrix4f transform_matrix) {
  origin_ = transform_matrix * origin_;
  direction_ = transform_matrix * direction_;
}

void Ray::GetTransform(Eigen::Matrix4f transform_matrix,
                       Eigen::Vector4f* origin, Eigen::Vector4f* direction) {
  //
  *origin = transform_matrix * origin_;
  *direction = transform_matrix * direction_;
}

// Method to intersect the ray with different objects
void Ray::IntersectObject(struct Object object) {
  // Transform the ray using the sphere.transform_ transformation
  if (object.object_type == ObjectType::SPHERE) {
    Eigen::Vector4f origin;
    Eigen::Vector4f direction;
    GetTransform((object.sphere.GetTransform()).inverse(), &origin, &direction);
    Eigen::Vector4f sphere_to_ray = origin - object.sphere.GetCenter();
    float a = direction.dot(direction);
    float b = 2 * (direction.dot(sphere_to_ray));
    float c = sphere_to_ray.dot(sphere_to_ray) -
              object.sphere.GetRadius() * object.sphere.GetRadius();
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
      return;
    }
    float t1 = (-b + sqrt(discriminant)) / (2 * a);
    float t2 = (-b - sqrt(discriminant)) / (2 * a);
    //
    struct Intersection* intersection1 = new Intersection(t1, object);
    struct Intersection* intersection2 = new Intersection(t2, object);
    AddIntersection(intersection1);
    AddIntersection(intersection2);
  }
}

void Ray::IntersectWorld(World world) {
  // Method to intersect the ray and the world
  std::vector<struct Object>& world_objects = world.GetObjects();
  for (int i = 0; i < world_objects.size(); i++) {
    IntersectObject(world_objects[i]);
  }
}

void Ray::AddIntersection(struct Intersection* intersection) {
  // Add intersection to the intersections_ vector
  intersections_.push_back(intersection);
  int intersections_size = intersections_.size();
  if (intersections_size < 2) {
    return;
  }
  for (int i = intersections_size - 2; i > -1; i--) {
    if ((intersections_[i + 1])->t_ < (intersections_[i])->t_) {
      struct Intersection* temp = intersections_[i];
      intersections_[i] = intersections_[i + 1];
      intersections_[i + 1] = temp;
    } else {
      return;
    }
  }
}

struct Intersection* Ray::PopIntersection() {
  for (auto intersection : intersections_) {
    if (intersection->GetT() >= 0) {
      return intersection;
    }
  }
  return nullptr;
}

struct Comps Ray::PrepareComputations(struct Intersection intersection) {
  //
  struct Comps comps;
  comps.t = intersection.GetT();
  // Intersection object
  comps.object = intersection.GetObject();

  comps.point = Position(intersection.GetT());
  comps.eyev = -GetDirection();
  comps.normalv = intersection.GetObject().sphere.NormalAt(comps.point);
  if (comps.normalv.dot(comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }
  return comps;
}

// Color At function
Eigen::Vector3f Ray::ColorAt(World& world) {
  // Step 1 Intersect world function
  IntersectWorld(world);

  // Obtain the hit for the ray
  struct Intersection* hit = PopIntersection();

  if (hit == nullptr) {
    return RGBColor(0, 0, 0);
  } else {
    struct Comps comps = PrepareComputations(*hit);
    return ShadeHit(world, comps);
  }
}

Eigen::Vector3f Ray::ShadeHit(World world, struct Comps& comps) {
  return Lighting(comps.object.sphere.GetMaterial(), world.GetLight(),
                  comps.point, comps.eyev, comps.normalv);
}
