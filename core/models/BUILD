package (default_visibility = ["//visibility:public"])

cc_library(
  name = "material",
  hdrs = ["material.h"],
  deps = [
    "@eigen",
  ]
)

cc_library(
  name = "object",
  hdrs = ["object.h"],
  deps = [
    "@eigen",
    ":sphere",
  ],
)

cc_library(
  name = "ray",
  srcs = ["ray.cc"],
  hdrs = ["ray.h"],
  deps = [
    "@eigen",
    ":freq_models",
    ":world",
    ":object",
  ],
)

cc_library(
  name = "vector",
  srcs = ["vector.cc",],
  hdrs = ["vector.h"],
  deps = [
    "@eigen",
  ],
)

cc_library(
  name = "light",
  srcs = ["light.cc"],
  hdrs = ["light.h"],
  deps = [
    "@eigen",
    ":material",
    "//core/ops:vector_ops",
    "//core/ops:color_ops",
  ]
)

cc_library(
  name = "basics",
  deps = [
    ":vector",
    "@eigen",
  ],
)

cc_library(
  name = "sphere",
  srcs = ["sphere.cc"],
  hdrs = ["sphere.h"],
  deps = [
    "@eigen",
    "//core/ops:vector_ops",
    "//core/models:material",
  ],
)

cc_library(
  name = "freq_models",
  deps = [
    ":basics",
    ":sphere",
  ],
)

cc_test(
  name = "freq_models_test",
  srcs = ["freq_models_test.cc"],
  deps = [
    ":freq_models",
  ],
)

cc_library(
  name = "world",
  srcs = ["world.cc"],
  hdrs = ["world.h"],
  deps = [
    ":freq_models",
    ":material",
    ":light",
    ":vector",
    ":object",
    "//core/ops:transformations",
    "@eigen",
  ],
)