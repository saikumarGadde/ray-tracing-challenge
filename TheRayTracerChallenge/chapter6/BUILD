package (default_visibility = ["//visibility:public"])

cc_library(
  name = "chapter6",
  srcs = ["chapter6.cc"],
  hdrs = ["chapter6.h"],
  deps = [
    "//TheRayTracerChallenge/chapter1:chapter1",
    "//TheRayTracerChallenge/chapter2:chapter2",
    "//TheRayTracerChallenge/chapter3:chapter3",
    "//TheRayTracerChallenge/chapter4:chapter4",
    "//TheRayTracerChallenge/chapter5:chapter5",
    "//core/protos:visualization_utils",
    "//core/protos:entities_3d",
    "@eigen",
  ]
)

cc_binary(
  name = "chapter6_main",
  srcs = ["chapter6_main.cc"],
  deps = [
    ":chapter6",
  ]
)

cc_test(
  name = "chapter6_test",
  srcs = ["chapter6_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":chapter6",
    "//external:gtest",
  ]
)