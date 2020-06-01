package(default_visibility=["//visibility:public"])

cc_library(
  name="chapter3",
  srcs=["chapter3.cc"],
  hdrs = ["chapter3.h"],
  deps=[
    "//core/chapter1:chapter1",
    "//core/chapter2:chapter2",
    "//core/protos:visualization_utils",
    "@eigen",
  ]
)

cc_test(
  name="chapter3_test",
  srcs=["chapter3_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    ":chapter3",
    "//external:gtest",
  ],
)