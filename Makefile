default:
	/usr/bin/clang++ -std=gnu++14 -stdlib=libc++ -g $(shell find . -name "*.cpp" ! -name "test*") -o ./chess

test:
	bazel test --cxxopt=-std=c++14 --test_output=all //:vecboard_test

clean:
	rm -r ./chess *.dSYM