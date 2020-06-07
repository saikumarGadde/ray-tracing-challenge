#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include "TheRayTracerChallenge/chapter6/chapter6.h"
#include "core/protos/visualization_utils.h"

// World data structure
class World {
 public:
  //   // Default Constructor for the World
  World(){
      // // Set transform of inner sphere
      // struct Sphere inner_sphere;
      // inner_sphere.transform = Scaling(0.5, 0.5, 0.5);
      // objects.push_back(Object(inner_sphere));
      // // Set material of outer sphere
      // struct Material outer_sphere_material(Color(0.8, 1.0, 0.6), 0.1, 0.7,
      // 0.2,
      //                                       200.0);
      // struct Sphere outer_sphere;
      // outer_sphere.material = outer_sphere_material;
      // objects.push_back(Object(outer_sphere));

      // light.intensity = Color(1, 1, 1);
      // light.point = Point1Dim(-10, -10, -10);
  };

  void AddObject(struct Object object) {
    // Add object to the objects vector
    objects.push_back(object);
  }

  // Point light
  struct PointLight light;
  // Vector of objects in the world
  std::vector<struct Object> objects;
};

struct Comps {
  // Object of intersection
  struct Object object;
  // Intersection at a distance
  float t;
  // Precomputations
  Eigen::Vector4f point;
  // Eye vector
  Eigen::Vector4f eyev;
  // Normal Vecotr to the plane
  Eigen::Vector4f normalv;
  // The light is Inside the object or outside the object
  bool inside;
};

// Implementing a Camera
struct Camera {
  Camera(float h_size_, float v_size_, float field_of_view_,
         Eigen::Matrix4f transform_ = Eigen::Matrix4f::Identity())
      : h_size(h_size_),
        v_size(v_size_),
        field_of_view(field_of_view_),
        transform(transform_) {
    PixelSize(h_size_, v_size_, field_of_view_, &pixel_size, &half_height,
              &half_width);
  };

  // Horizontal size of the canvas that the picture will be rendered to
  float h_size;
  // Vertical size of the canvas that the picture will be rendered to
  float v_size;
  // Field of view of the Camera
  float field_of_view;
  // Transformation describing how the world should be oriented relative to
  // camera
  Eigen::Matrix4f transform;
  // Set the pixel size on the canvas
  float pixel_size;
  // Half height of the canvas
  float half_height;
  // Half Width of the canvas
  float half_width;

  // Obtain the pixel size of the canvas
  void PixelSize(float hsize, float vsize, float fieldofview, float* pixelsize,
                 float* halfheight, float* halfwidth) {
    float half_view = tan(fieldofview / 2.0);
    float aspect = hsize / vsize;
    if (aspect >= 1) {
      *halfwidth = half_view;
      *halfheight = half_view / aspect;
    } else {
      *halfwidth = half_view * aspect;
      *halfheight = half_view;
    }
    *pixelsize = ((*halfwidth) * 2) / hsize;
  }
};

// Method to intersect the ray and the world
std::vector<struct Intersection*> IntersectWorld(struct Ray ray, World world);

// Prepare computations
struct Comps PrepareComputations(struct Intersection intersection,
                                 struct Ray ray);

// Shade hit function
Eigen::Vector3f ShadeHit(World world, struct Comps comps);

// Returns the color ar an intersection point of the ray and the world
Eigen::Vector3f ColorAt(World& world, struct Ray ray);

// Transformation matrix for the camera
Eigen::Matrix4f ViewTransformation(Eigen::Vector4f from, Eigen::Vector4f to,
                                   Eigen::Vector4f up);

// Cross product of two eigen vectors in C++
Eigen::Vector4f CrossProduct4f(Eigen::Vector4f vector1,
                               Eigen::Vector4f vector2);

// Ray for Pixel
struct Ray RayToPixel(struct Camera camera, float px, float py);

// Render the world form camera
void Render(struct Camera camera, World world, struct Canvas* canvas);

// Chapter7Task
void Chapter7Task(std::string canvas_file_path);

void PixelWrite(int height, int width, struct RGBColor color,
                struct Canvas* canvas);

void CanvasPPM(struct Canvas* canvas, const char ppm_file_path[]);