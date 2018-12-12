CC=clang
CFLAGS= -I include
LDFLAGS= 
BINARY=rwfloatbin
BINARY_TESTS=rwfloatbin_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

rwfloat: main.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^

aiv_file.o: include/aiv_file.h
	$(CC) -c -o $@ $(CFLAGS) $^

tests.o: tests/tests.c
	$(CC) -c -o $@ $(CFLAGS) $^

test: tests.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean:
	rm -f *.o