package(default_visibility=["//visibility:public"])

cc_library(
  name = "chapter4",
  srcs = ["chapter4.cc"],
  hdrs = ["chapter4.h"],
  deps = [
    "//core/chapter1:chapter1",
    "//core/chapter2:chapter2",
    "//core/chapter3:chapter3",
    "//core/protos:visualization_utils",
    "@eigen",
  ],
)

cc_test(
  name = "chapter4_test",
  srcs = ["chapter4_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":chapter4",
    "//external:gtest",
  ],
)