cc_library(
    name = "gtest",
    srcs = glob([
            "googlemock/include/**/*.h",
            "googlemock/src/*.cc",
            "googlemock/src/*.h",
            "googletest/include/**/*.h",
            "googletest/src/*.cc",
            "googletest/src/*.h",
        ],
        exclude = [
            "googlemock/src/gmock-all.cc",
            "googletest/src/gtest-all.cc",
            "googletest/src/gtest_main.cc",
        ],
    ),
    hdrs = glob([
        "googlemock/include/gmock/gmock.h",
        "googletest/include/gtest/gtest.h",
    ]),
    copts = [
        "-Iexternal/gtest_git/googlemock",
        "-Iexternal/gtest_git/googlemock/include",
        "-Iexternal/gtest_git/googletest",
        "-Iexternal/gtest_git/googletest/include",
    ],
    includes = [
        "googlemock/include",
        "googletest/include",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
