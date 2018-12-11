CC=clang
CFLAGS= -Wno-pragma-pack -I SDL/include -I include
LDFLAGS=-lSDL2 -L SDL/lib/x64
BINARY=challenge
BINARY_TESTS=challenge_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

challenge: main.o aiv_context.o aiv_clock.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^

aiv_context.o: src/aiv_context.c include/aiv_context.h
	$(CC) -c -o $@ $(CFLAGS) $<

aiv_clock.o: src/aiv_clock.c include/aiv_clock.h
	$(CC) -c -o $@ $(CFLAGS) $<

tests.o: tests/tests.c
	$(CC) -c -o $@ $(CFLAGS) $^

test: tests.o aiv_clock.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
