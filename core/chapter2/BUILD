package(default_visibility=["//visibility:public"])

cc_library(
  name="chapter2",
  srcs=["chapter2.cc"],
  hdrs=["chapter2.h"],
  deps=[
    "//core/chapter1:chapter1",
    "//core/protos:visualization_utils",
  ]
)

cc_test(
  name="chapter2_test",
  srcs=["chapter2_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    ":chapter2",
    "//external:gtest",
  ]
)