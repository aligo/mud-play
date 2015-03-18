CC=clang
LD=ld

FRAMEWORKS:= -framework Foundation
LIBRARIES:= -lobjc

CFLAGS=-Wall -Werror -g -v
LDFLAGS=$(LIBRARIES) $(FRAMEWORKS)

BINDIR   = build

MUD_CORE_DIR			= src
MUD_CORE_INCLUDE	=	-include $(MUD_CORE_DIR)/mud.h
MUD_CORE_SRCS			=	$(wildcard $(MUD_CORE_DIR)/*.c) $(wildcard $(MUD_CORE_DIR)/*/*.c)
MUD_CORE_OBJS			=	$(MUD_CORE_SRCS:$(MUD_CORE_DIR)/%.c=mud/%.o)

BRIDGE_OPERATORS_INCLUDE=-include tmp/ns_bridge_operators.h
BRIDGE_OPERATORS_FILES=tmp/ns_bridge_operators.c
BRIDGE_INCLUDE=-include src/bridges/ns/bridge.h
BRIDGE_FILES=src/bridges/ns/bridge.m

# all: run

# prepare:
# 	mkdir -p ./build/tests
# 	./scripts/prepare_operators.rb

# main: prepare
# 	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o build/$@

# run: main
# 	./build/main

# test:
# 	mkdir -p ./build/tests
# 	./scripts/prepare_operators.rb ../tmp/ns_bridge
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(MUD_INCLUDE) $(BRIDGE_OPERATORS_INCLUDE) $(BRIDGE_INCLUDE) $(MUD_FILES) $(BRIDGE_OPERATORS_FILES) $(BRIDGE_FILES) tests/$(TEST).m -o build/tests/$(TEST)
# 	./build/tests/$(TEST)

clean:
	rm -Rf ./build

mud_core: $(MUD_CORE_OBJS)
	$(LD) -r $(MUD_CORE_OBJS:%.o=$(BINDIR)/%.o) -o $(BINDIR)/mud.o

$(MUD_CORE_OBJS): mud/%.o : $(MUD_CORE_DIR)/%.c
	@mkdir -p $(BINDIR)/$(@D)
	$(CC) $(MUD_CORE_INCLUDE) -c $< -o $(BINDIR)/$@

# test_date: mud_ns_bridge
# 	$(CC) $(CFLAGS) $(LDFLAGS) tests/date.m build/mud_ns_bridge -o build/$@