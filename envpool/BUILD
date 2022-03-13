load("@pip_requirements//:requirements.bzl", "requirement")

package(default_visibility = ["//visibility:public"])

exports_files([
    "workspace0.bzl",
    "workspace1.bzl",
])

py_library(
    name = "registration",
    srcs = ["registration.py"],
)

py_library(
    name = "entry",
    srcs = ["entry.py"],
    deps = [
        "//envpool/classic_control:classic_control_registration",
    ],
)

py_library(
    name = "envpool",
    srcs = ["__init__.py"],
    deps = [
        ":entry",
        ":registration",
        "//envpool/classic_control",
        "//envpool/python",
    ],
)

