cc_library(
    name = "vecboard",
    srcs = ["GameBoard.cpp", "VecBoard.cpp"],
    hdrs = ["GameBoard.h", "VecBoard.h", "Piece.h"],
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