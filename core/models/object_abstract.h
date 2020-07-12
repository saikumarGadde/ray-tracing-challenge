#pragma once
#include <Eigen/Core>
#include "core/models/material.h"
#include "core/models/object_type.h"

class ObjectAbstract {
 public:
  ObjectAbstract(object_type::ObjectType object_type)
      : object_type_(object_type) {}

  virtual ~ObjectAbstract() {}

  void InitObject(object_type::ObjectType object_type);

  //  Setters
  void SetTransform(Eigen::Matrix4f transform);
  void SetMaterial(struct Material material);

  Eigen::Matrix4f& GetTransform();
  struct Material& GetMaterial();

  virtual Eigen::Vector4f NormalAt(Eigen::Vector4f point) = 0;
  Eigen::Vector4f NormalAtWorldPoint(Eigen::Vector4f world_point);

  // GetObjectType
  object_type::ObjectType GetObjectType();

 protected:
  Eigen::Matrix4f transform_;
  struct Material material_;
  object_type::ObjectType object_type_;
};