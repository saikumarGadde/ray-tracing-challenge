#include "core/models/ray.h"

Eigen::Vector4f Ray::Position(const float distance) const {
  return origin_ + (direction_ * distance);
}

void Ray::SetTransform(Eigen::Matrix4f& transform_matrix) {
  origin_ = transform_matrix * origin_;
  direction_ = transform_matrix * direction_;
}

void Ray::GetTransform(Eigen::Matrix4f& transform_matrix,
                       Eigen::Vector4f* origin, Eigen::Vector4f* direction) {
  //
  *origin = transform_matrix * origin_;
  *direction = transform_matrix * direction_;
}

// Method to intersect the ray with different objects
void Ray::IntersectObject(Object& object) {
  // Transform the ray using the sphere.transform_ transformation
  if (object.GetObjectType() == object_type::ObjectType::SPHERE) {
    Eigen::Vector4f origin;
    Eigen::Vector4f direction;
    Eigen::Matrix4f object_transform_inverse =
        (object.GetTransform()).inverse();
    GetTransform(object_transform_inverse, &origin, &direction);
    Eigen::Vector4f sphere_to_ray = origin - object.GetCenter();
    float a = direction.dot(direction);
    float b = 2 * (direction.dot(sphere_to_ray));
    float c = sphere_to_ray.dot(sphere_to_ray) -
              object.GetRadius() * object.GetRadius();
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
      return;
    }
    float t1 = (-b + sqrt(discriminant)) / (2 * a);
    float t2 = (-b - sqrt(discriminant)) / (2 * a);
    //
    struct Intersection* intersection1 = new Intersection(t1, &object);
    struct Intersection* intersection2 = new Intersection(t2, &object);
    AddIntersection(intersection1);
    AddIntersection(intersection2);
  }
}

void Ray::IntersectWorld(World& world) {
  // Method to intersect the ray and the world
  std::vector<Object>& world_objects = world.GetObjects();
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

void Ray::PrepareComputations(struct Intersection* hit, struct Comps* comps) {
  //
  comps->t = hit->GetT();
  // Hit object
  comps->object = hit->GetObject();

  comps->point = Position(hit->GetT());
  comps->eyev = -GetDirection();
  comps->normalv = (hit->GetObject())->NormalAtWorldPoint(comps->point);
  if ((comps->normalv).dot(comps->eyev) < 0) {
    comps->inside = true;
    comps->normalv = -comps->normalv;
  } else {
    comps->inside = false;
    comps->over_point = (comps->point) + (comps->normalv * 0.01);
  }
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
    struct Comps comps;
    PrepareComputations(hit, &comps);
    return ShadeHit(world, comps);
    // return RGBColor(1, 1, 1);
  }
}

Eigen::Vector3f Ray::ShadeHit(World& world, struct Comps& comps) {
  bool is_shadowed = IsShadowed(world, comps.over_point);
  return Lighting2(comps.object->GetMaterial(), world.GetLight(),
                   comps.over_point, comps.eyev, comps.normalv, is_shadowed);
}

// Calculate the reflection
Eigen::Vector4f Ray::Reflect(Eigen::Vector4f in, Eigen::Vector4f normal) {
  // @
  Eigen::Vector4f reflection = in - (normal * 2 * in.dot(normal));
  return reflection;
};

Eigen::Vector3f Ray::Lighting2(struct Material material,
                               struct PointLight point_light,
                               Eigen::Vector4f position, Eigen::Vector4f eyev,
                               Eigen::Vector4f normalv, bool in_shadow) {
  // Combine the surface color with the lights color/intensity
  Eigen::Vector3f effective_color =
      RGBColorMultiply(material.rgb_color, point_light.GetIntensity());

  // Find the direction of the color source
  Eigen::Vector4f lightv =
      Normalization(point_light.GetLightPosition() - position);

  // Compute the ambient contribution
  Eigen::Vector3f ambient = effective_color * material.ambient;

  // light_dot_normal
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  float light_dot_normal = lightv.dot(normalv);
  if (light_dot_normal < 0) {
    diffuse = Eigen::Vector3f::Zero();
    specular = Eigen::Vector3f::Zero();
  } else {
    // Diffuse contribution
    diffuse = effective_color * material.diffuse * light_dot_normal;
    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the light
    // reflects away from the eye
    Eigen::Vector4f reflectv = Reflect(-lightv, normalv);
    float reflect_dot_eye = reflectv.dot(eyev);
    if (reflect_dot_eye <= 0) {
      specular = Eigen::Vector3f::Zero();
    } else {
      float factor = pow(reflect_dot_eye, material.shininess);
      specular = point_light.GetIntensity() * material.specular * factor;
    }
  }
  if (in_shadow == true) {
    return ambient;
  }
  return ambient + diffuse + specular;
};

bool Ray::IsShadowed(World& world, Eigen::Vector4f point) {
  //
  Eigen::Vector4f v = world.GetLight().GetLightPosition() - point;
  float distance = v.norm();
  Eigen::Vector4f direction = Normalization(v);

  // Obtain a ray from the point of intersection to the light in World
  Ray ray(point, direction);
  ray.IntersectWorld(world);

  struct Intersection* hit = ray.PopIntersection();
  if ((hit != nullptr) && (hit->GetT() < distance)) {
    return true;
  }
  return false;
}