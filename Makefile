build-test: test.c cvec.h
	clang test.c -o test -g

run-test: test
	./test

