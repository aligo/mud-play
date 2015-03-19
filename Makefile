define \n


endef

CC=clang
LD=ld

FRAMEWORKS:= -framework Foundation
LIBRARIES:= -lobjc

CFLAGS=-Wall -Werror -g
LDFLAGS=$(LIBRARIES) $(FRAMEWORKS)

BINDIR   									= build

TMP_DIR             			= tmp

MUD_CORE_DIR							=	src
MUD_CORE_INCLUDE					=	-include $(MUD_CORE_DIR)/mud.h
MUD_CORE_SRCS							=	$(wildcard $(MUD_CORE_DIR)/*.c) $(wildcard $(MUD_CORE_DIR)/*/*.c)
MUD_CORE_OBJS							=	$(MUD_CORE_SRCS:$(MUD_CORE_DIR)/%.c=mud/%.o)

MUD_CORE_OPERATORS_DIR  	= operators
MUD_CORE_OPERATORS_SRCS   = $(wildcard $(MUD_CORE_OPERATORS_DIR)/*.c)

BRIDGES_DIR								= bridges
NS_BRIDGE_INCLUDE 				= -include bridges/ns/bridge.h

NS_BRIDGE_OPERATORS_DIR		= bridges/ns/operators
NS_BRIDGE_OPERATORS_SRCS  = $(wildcard $(NS_BRIDGE_OPERATORS_DIR)/*.m)

TEST_DIR									=	tests
TEST_SRCS         				= $(wildcard $(TEST_DIR)/*.m)
TEST_EXEC         				= $(TEST_SRCS:$(TEST_DIR)/%.m=$(TEST_DIR)/%)

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

$(MUD_CORE_OBJS):
	@mkdir -p $(BINDIR)/$(@D)
	$(CC) $(MUD_CORE_INCLUDE) -c $(@:mud/%.o=$(MUD_CORE_DIR)/%.c) -o $(BINDIR)/$@

ns_bridge:
	$(CC) $(MUD_CORE_INCLUDE) $(NS_BRIDGE_INCLUDE) -c $(BRIDGES_DIR)/ns/bridge.m -o $(BINDIR)/ns_bridge.o

ns_operators:
	./scripts/prepare_operators.rb -a $(MUD_CORE_OPERATORS_DIR) -a $(NS_BRIDGE_OPERATORS_DIR) -o $(TMP_DIR)
	@rm -rf $(BINDIR)/operators
	@mkdir -p $(BINDIR)/operators
	$(CC) $(MUD_CORE_INCLUDE) $(NS_BRIDGE_INCLUDE) -include $(TMP_DIR)/_operators.h -c $(TMP_DIR)/_operators.c -o $(BINDIR)/operators/_operators.o
	$(foreach operator, $(MUD_CORE_OPERATORS_SRCS) $(NS_BRIDGE_OPERATORS_SRCS), \
		@mkdir -p $(dir $(BINDIR)/operators/$(notdir $(basename $(operator)))) $(\n) \
		$(CC) $(MUD_CORE_INCLUDE) $(NS_BRIDGE_INCLUDE) -include $(TMP_DIR)/_operators.h -c $(operator) -o $(BINDIR)/operators/$(notdir $(basename $(operator))).o $(\n) \
	)
	$(LD) -r $(wildcard $(BINDIR)/operators/*.o) -o $(BINDIR)/ns_operators.o

$(TEST_EXEC): mud_core ns_bridge ns_operators
	@mkdir -p $(BINDIR)/tests
	$(CC) $(CFLAGS) $(LDFLAGS) $(MUD_CORE_INCLUDE) $(NS_BRIDGE_INCLUDE) -include $(TMP_DIR)/_operators.h \
		$(BINDIR)/mud.o $(BINDIR)/ns_bridge.o $(BINDIR)/ns_operators.o \
		$(TEST_DIR)/support.m $(@:$(TEST_DIR)/%=$(TEST_DIR)/%.m) \
		-o $(BINDIR)/$@
	./$(BINDIR)/$@
