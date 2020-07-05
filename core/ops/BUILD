package(default_visibility = ["//visibility:public"])

cc_library(
  name = "vector_ops",
  srcs = ["vector_ops.cc"],
  hdrs = ["vector_ops.h"],
  deps = [
    "@eigen",
  ]
)

cc_library(
  name = "color_ops",
  srcs = ["color_ops.cc"],
  hdrs = ["color_ops.h"],
  deps = [
    "@eigen",
  ],
)

cc_test(
  name = "vector_ops_test",
  srcs = ["vector_ops_test.cc"],
  deps = [
    ":vector_ops",
  ]
)

cc_library(
  name = "transformations",
  srcs = ["transformations.cc"],
  hdrs = ["transformations.h"],
  deps = [
    "@eigen",
    "//core/ops:vector_ops",
  ]
)

cc_test(
  name = "transformations_test",
  srcs = ["transformations_test.cc"],
  deps = [
    ":transformations",
  ],
)

cc_library(
  name = "math_ops",
  srcs = ["math_ops.cc"],
  hdrs = ["math_ops.h"],
)