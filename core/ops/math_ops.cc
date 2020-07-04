#include "core/ops/math_ops.h"

// Count number of digits in an integer
int NumberOfDigitsInInteger(int number) {
  return std::floor(log10(number) + 1);
}