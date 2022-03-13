load("@pip_requirements//:requirements.bzl", "requirement")
load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

py_library(
    name = "dummy",
    srcs = ["__init__.py"],
    data = [":dummy_envpool.so"],
    deps = ["//envpool/python:api"],
)

cc_library(
    name = "dummy_envpool_h",
    hdrs = ["dummy_envpool.h"],
    deps = [
        "//envpool/core:async_envpool",
        "//envpool/core:env",
        "//envpool/core:env_spec",
    ],
)

pybind_extension(
    name = "dummy_envpool",
    srcs = [
        "dummy_envpool.cc",
    ],
    linkopts = [
        "-ldl",
    ],
    deps = [
        ":dummy_envpool_h",
        "//envpool/core:py_envpool",
    ],
)
