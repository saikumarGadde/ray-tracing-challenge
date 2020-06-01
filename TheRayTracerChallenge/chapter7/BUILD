package (default_visibility = ["//visibility:public"])

cc_library(
  name = "chapter7",
  srcs = ["chapter7.cc"],
  hdrs = ["chapter7.h"],
  deps = [
    "//core/chapter1:chapter1",
    "//core/chapter2:chapter2",
    "//core/chapter3:chapter3",
    "//core/chapter4:chapter4",
    "//core/chapter5:chapter5",
    "//core/chapter6:chapter6",
    "//core/protos:visualization_utils",
    "//core/protos:entities_3d",
    "@eigen",
  ]
)

cc_binary(
  name = "chapter7_main",
  srcs = ["chapter7_main.cc"],
  deps = [
    ":chapter7",
  ],
)

cc_test(
  name = "chapter7_test",
  srcs = ["chapter7_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":chapter7",
    "//external:gtest",
  ],
)