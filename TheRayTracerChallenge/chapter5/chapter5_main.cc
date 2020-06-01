#include "TheRayTracerChallenge/chapter5/chapter5.h"

//

int main(int argc, char* argv[]) {
  // Number of pixels in the canvas
  float canvas_pixels = 100;
  // Size of the wall
  float wall_size = 7;
  // Wall location on the z axis
  float wall_z = 10;
  // Path of the canvas file
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/wow.ppm";

  Chapter5Task(canvas_pixels, wall_size, wall_z, canvas_file_path);
}