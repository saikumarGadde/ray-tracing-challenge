package(default_visibility=["//visibility:public"])

cc_library(
  name="chapter1",
  srcs=["chapter1.cc"],
  hdrs=["chapter1.h"],
  deps=[
    "//core/protos:entities_3d",
  ]
)

cc_test(
  name="chapter1_test",
  srcs=["chapter1_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    "//external:gtest",
    ":chapter1",
  ],
)