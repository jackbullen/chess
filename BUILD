cc_library(
    name = "vecboard",
    srcs = ["VecBoard.cpp"],
    hdrs = ["VecBoard.h", "Piece.h"],
)

cc_test(
    name = "vecboard_test",
    size = "small",
    srcs = ["tests_vecboard.cpp"],
    deps = [
        ":vecboard",
        "@com_google_googletest//:gtest_main",
    ],
)