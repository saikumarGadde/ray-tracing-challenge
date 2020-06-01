#include "core/chapter6/chapter6.h"

int main(int argc, char* argv[]) {
  //
  float canvas_pixels = 1000;
  // Size of the wall
  float wall_size = 7;
  // Wall location on the z axis
  float wall_z = 10;
  // Path of the canvas file
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/wow2.ppm";

  Chapter6Task(canvas_pixels, wall_size, wall_z, canvas_file_path);
}