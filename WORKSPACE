workspace(name = "parrotdb")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Gflags.

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "19713a36c9f32b33df59d1c79b4958434cb005b5b47dc5400a7a4b078111d9b5",
    strip_prefix = "gflags-2.2.2",
    url = "https://github.com/gflags/gflags/archive/v2.2.2.zip",
)

# Glog.

http_archive(
    name = "glog",
    sha256 = "9e1b54eb2782f53cd8af107ecf08d2ab64b8d0dc2b7f5594472f3bd63ca85cdc",
    strip_prefix = "glog-0.4.0",
    url = "https://github.com/google/glog/archive/v0.4.0.zip",
)

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
