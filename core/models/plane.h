#pragma once
#include "core/models/object_abstract.h"
#include "core/models/object_type.h"
#include "core/models/vector.h"
#include "core/ops/vector_ops.h"

class Plane : public ObjectAbstract {
 public:
  // Plane constructor
  Plane(object_type::ObjectType object_type) : ObjectAbstract(object_type) {}

  virtual ~Plane() {}

  Eigen::Vector4f NormalAt(Eigen::Vector4f point);

  void InitPlane();

 private:
  //
};