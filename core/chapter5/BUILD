package(default_visibility=["//visibility:public"])

cc_library(
  name = "chapter5",
  srcs = ["chapter5.cc"],
  hdrs = ["chapter5.h"],
  deps = [
    "//core/chapter1:chapter1",
    "//core/chapter2:chapter2",
    "//core/chapter3:chapter3",
    "//core/chapter4:chapter4",
    "//core/protos:visualization_utils",
    "@eigen",
  ],
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