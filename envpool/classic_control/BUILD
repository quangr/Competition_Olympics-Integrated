load("@pip_requirements//:requirements.bzl", "requirement")
load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cartpole",
    hdrs = ["cartpole.h"],
    deps = [
        "//envpool/core:async_envpool",
    ],
)

pybind_extension(
    name = "classic_control_envpool",
    srcs = [
        "classic_control.cc",
    ],
    deps = [
        ":cartpole",
        "//envpool/core:py_envpool",
    ],
)

py_library(
    name = "classic_control",
    srcs = ["__init__.py"],
    data = [":classic_control_envpool.so"],
    deps = ["//envpool/python:api"],
)

py_test(
    name = "classic_control_test",
    srcs = ["classic_control_test.py"],
    deps = [
        ":classic_control",
        requirement("numpy"),
        requirement("absl-py"),
    ],
)

py_library(
    name = "classic_control_registration",
    srcs = ["registration.py"],
    deps = [
        "//envpool:registration",
    ],
)