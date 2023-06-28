CC = clang
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
SRC := $(wildcard src/*.c)
OUT_DIR = out
OUT = $(OUT_DIR)/snake

RAYLIB = $(shell pkg-config --cflags --libs raylib)

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(RAYLIB)

run: $(OUT)
	./$(OUT)

clean:
	rm -rf $(OUT_DIR)
