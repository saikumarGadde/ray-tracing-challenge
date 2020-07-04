

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
