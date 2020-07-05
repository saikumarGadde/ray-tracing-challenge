package(default_visibility=["//visibility:public"])


cc_library(
  name = "libs",
  deps = [
    "//external:gtest",
    "//core/ops:vector_ops",
    "//core/visual:canvas",
    "//core/ops:color_ops",
    "//core/ops:transformations",
    "//core/models:freq_models",
    "//core/models:ray",
    "//core/models:light",
    "//core/models:camera",
    "@eigen",
  ]
)

cc_test(
  name="chapter1_test",
  srcs=["chapter1_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    ":libs",
  ],
)

cc_test(
  name="chapter2_test",
  srcs=["chapter2_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    ":libs",
  ],
)

cc_test(
  name="chapter3_test",
  srcs=["chapter3_test.cc"],
  copts=["-Iexternal/gtest/include"],
  deps=[
    ":libs",
  ],
)


cc_test(
  name = "chapter4_test",
  srcs = ["chapter4_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":libs",
  ],
)

cc_test(
  name = "chapter5_test",
  srcs = ["chapter5_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":libs",
  ],
)


cc_test(
  name = "chapter6_test",
  srcs = ["chapter6_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":libs",
  ]
)

cc_test(
  name = "chapter7_test",
  srcs = ["chapter7_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    ":libs",
    "//core:ray_tracing_processor",
  ],
)