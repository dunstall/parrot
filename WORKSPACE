workspace(name = "parrotdb")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Google Test.

http_archive(
    name = "gtest",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
)

# GRPC.

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "c35d405f9979f78b4d3cc6ddb2f3b85f59a616c974c1f86ee56fa57ed3e6800a",
    strip_prefix = "grpc-56ad644c329d90c0742a02462b2bd365ff759158",
    urls = [
        "https://github.com/grpc/grpc/archive/56ad644c329d90c0742a02462b2bd365ff759158.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

# TODO(AD) Add clang-tidy and cpplint to bazel
# TODO(AD) Do bazel properly

# spdlog

http_archive(
    name = "spdlog",
    build_file = "BUILD.spdlog",
    sha256 = "f0114a4d3c88be9e696762f37a7c379619443ce9d668546c61b21d41affe5b62",
    strip_prefix = "spdlog-1.7.0",
    urls = [
        "https://github.com/gabime/spdlog/archive/v1.7.0.tar.gz",
    ],
)
