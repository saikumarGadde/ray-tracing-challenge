# External dependency definition

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")



new_git_repository(
    name = "gtest_git",
    build_file = "@//:BUILD.gtest",
    commit = "d225acc90bc3a8c420a9bcd1f033033c1ccd7fe0",
    remote = "https://github.com/google/googletest.git",
)

bind(
    name = "gtest",
    actual = "@gtest_git//:gtest",
)
