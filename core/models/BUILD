package (default_visibility = ["//visibility:public"])

cc_library(
  name = "material",
  hdrs = ["material.h"],
  deps = [
    "@eigen",
  ]
)

cc_library(
  name = "camera",
  srcs = ["camera.cc"],
  hdrs = ["camera.h"],
  deps = [
    "@eigen",
    "//core/models:ray",
    "//core/ops:vector_ops",
  ],
)

cc_library(
  name = "ray",
  srcs = ["ray.cc"],
  hdrs = ["ray.h"],
  deps = [
    "@eigen",
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
  hdrs = ["light.h"],
  deps = [
    "@eigen",
    ":material",
    "//core/ops:vector_ops",
    "//core/ops:color_ops",
  ]
)


cc_library(
  name = "object",
  srcs = ["object.cc"],
  hdrs = ["object.h"],
  deps = [
    ":sphere",
    ":plane",
    ":object_type",
  ],
)

cc_library(
  name = "object_type",
  hdrs = ["object_type.h"]
)

cc_library(
  name = "phong_model",
  hdrs = ["phong_model.h"],
  srcs = ["phong_model.cc"],
  deps = [
    "//core/models:light",
    "//core/models:ray",
    "@eigen",
  ],
)

cc_library(
  name = "sphere",
  srcs = ["sphere.cc"],
  hdrs = ["sphere.h"],
  deps = [
    ":object_type",
    ":material",
    ":object_abstract",
    "//core/ops:vector_ops",
    "//core/models:vector",
    "@eigen",
  ],
)

cc_library(
  name = "plane",
  srcs = ["plane.cc"],
  hdrs = ["plane.h"],
  deps = [
    ":object_type",
    ":material",
    ":object_abstract",
    "//core/models:vector",
    "//core/ops:vector_ops",
    "@eigen",
  ],
)

cc_library(
  name = "object_abstract",
  srcs = ["object_abstract.cc"],
  hdrs = ["object_abstract.h"],
  deps = [
    ":material",
    ":object_type",
    "//core/ops:vector_ops",
    "@eigen",
  ]
)

cc_library(
  name = "world",
  srcs = ["world.cc"],
  hdrs = ["world.h"],
  deps = [
    ":light",
    ":vector",
    ":object",
    "//core/ops:transformations",
    "@eigen",
  ],
)