package(default_visibility=["//visibility:public"])

cc_library(
  name = "chapter5",
  srcs = ["chapter5.cc"],
  hdrs = ["chapter5.h"],
  deps = [
    "//TheRayTracerChallenge/chapter1:chapter1",
    "//TheRayTracerChallenge/chapter2:chapter2",
    "//TheRayTracerChallenge/chapter3:chapter3",
    "//TheRayTracerChallenge/chapter4:chapter4",
    "//core/protos:visualization_utils",
    "//core/protos:entities_3d",
    "@eigen",
  ],
)

cc_binary(
  name = "chapter5_main",
  srcs = ["chapter5_main.cc"],
  deps = [
    ":chapter5",
  ]
)

cc_test(
  name = "chapter5_test",
  srcs = ["chapter5_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":chapter5",
    "//external:gtest",
  ],
)