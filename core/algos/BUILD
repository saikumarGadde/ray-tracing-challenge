package(default_visibility=["//visibility:public"])

cc_library(
  name = "heap",
  srcs = [heap.cc],
  hdrs = ["heap.h"],

)

cc_test(
  name = "heap_test",
  srcs = ["heap.cc"],
  hdrs = ["heap.h"],
  deps = [
    ":heap",
  ]
)

cc_library(
  name = "kd_tree",
  srcs = "kd_tree.cc",
  hdrs = ["kd_tree.h"],

)

cc_test (
  name = "kd_tree_test",
  srcs = ["kd_tree_test.cc"],
  deps = [
    ":kd_tree",
  ],
)