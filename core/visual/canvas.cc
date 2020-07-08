#include "core/visual/canvas.h"

// Add color to a pixel in canvas
void Canvas::WritePixel(uint64_t y, uint64_t x, Eigen::Vector3f color) {
  canvas_[y][x] = color;
}

Eigen::Vector3f Canvas::GetPixel(uint64_t y, uint64_t x) {
  return canvas_[y][x];
}

// Wite Canvas to PPM File
void Canvas::CanvasToPPM(const char ppm_file_path[]) {
  // Open a PPM File
  FILE* fp = fopen(ppm_file_path, "w");
  // Write header to the PPM File
  fprintf(fp, "P3\n%d %d\n255\n", GetWidth(), GetHeight());
  int r, g, b;
  int count = 0;
  for (int y = 0; y < GetHeight(); y++) {
    for (int x = 0; x < GetWidth(); x++) {
      Eigen::Vector3f pixel_color = canvas_[y][x];
      r = std::max(0, std::min((int)(pixel_color(0) * 255), 255));
      g = std::max(0, std::min((int)(pixel_color(1) * 255), 255));
      b = std::max(0, std::min((int)(pixel_color(2) * 255), 255));
      fprintf(fp, "%d ", r);
      fprintf(fp, "%d ", g);
      fprintf(fp, "%d ", b);
      count += 12;
      if (count > 70) {
        count = 0;
        fprintf(fp, "\n");
      }
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

void Canvas::PPMToCanvas(const char ppm_file_path[]) {
  FILE* fp = fopen(ppm_file_path, "r");
}
