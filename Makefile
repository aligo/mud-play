CC=clang

FRAMEWORKS:= -framework Foundation
LIBRARIES:= -lobjc

CFLAGS=-Wall -Werror -g -v
LDFLAGS=$(LIBRARIES) $(FRAMEWORKS)
OUT=main

all: run

prepare:
	mkdir -p ./build/tests
	./scripts/prepare_operators.rb

main: prepare
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o build/$@

run: main
	./build/main

test: prepare
	$(CC) $(CFLAGS) tests/$(TEST).m $(LDFLAGS) -o build/tests/$(TEST)
	./build/tests/$(TEST)

clean:
	rm -Rf ./build