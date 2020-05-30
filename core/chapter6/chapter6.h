#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "core/protos/visualization_utils.h"

Eigen::Vector4f NormalAt(struct Sphere sphere, Eigen::Vector4f& point);