CC=clang

FRAMEWORKS:= -framework Foundation
LIBRARIES:= -lobjc

CFLAGS=-Wall -Werror -g -v
LDFLAGS=$(LIBRARIES) $(FRAMEWORKS)

MUD_INCLUDE=-include src/mud.h
MUD_FILES=$(wildcard src/*.c) $(wildcard src/*/*.c)
BRIDGE_OPERATORS_INCLUDE=-include tmp/ns_bridge_operators.h
BRIDGE_OPERATORS_FILES=tmp/ns_bridge_operators.c
BRIDGE_INCLUDE=-include src/bridges/ns/bridge.h
BRIDGE_FILES=src/bridges/ns/bridge.m

all: run

prepare:
	mkdir -p ./build/tests
	./scripts/prepare_operators.rb

main: prepare
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o build/$@

run: main
	./build/main

test:
	mkdir -p ./build/tests
	./scripts/prepare_operators.rb ../tmp/ns_bridge
	$(CC) $(CFLAGS) $(LDFLAGS) $(MUD_INCLUDE) $(BRIDGE_OPERATORS_INCLUDE) $(BRIDGE_INCLUDE) $(MUD_FILES) $(BRIDGE_OPERATORS_FILES) $(BRIDGE_FILES) tests/$(TEST).m -o build/tests/$(TEST)
	./build/tests/$(TEST)

clean:
	rm -Rf ./build