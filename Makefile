CPP_FILES := $(wildcard *.cpp)
TEST_FILES := $(wildcard tests*.cpp)
SOURCE_FILES := $(filter-out $(TEST_FILES), $(CPP_FILES))

default:
	/usr/bin/clang++ -g -std=gnu++14 $(SOURCE_FILES) -o ./chess

fed:
	g++ -g $(SOURCE_FILES) -o ./chess

test:
	bazel test --test_output=all //:vecboard_test

clean:
	rm -r ./chess *.dSYM