#include "core/models/ray.h"

Eigen::Vector4f Ray::Position(const float distance) const {
  return origin_ + (direction_ * distance);
}

void Ray::SetTransform(Eigen::Matrix4f transform_matrix) {
  origin_ = transform_matrix * origin_;
  direction_ = transform_matrix * direction_;
}

// Method to intersect the ray with different objects
void Ray::IntersectObject(struct Object object) {
  // Transform the ray using the sphere.transform_ transformation
  if (object.object_type == ObjectType::SPHERE) {
    SetTransform((object.sphere.GetTransform()).inverse());
    Eigen::Vector4f sphere_to_ray = origin_ - object.sphere.GetCenter();
    float a = direction_.dot(direction_);
    float b = 2 * (direction_.dot(sphere_to_ray));
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
  std::vector<struct Intersection*> intersections;
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
