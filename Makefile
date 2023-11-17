TARGET = display-test
VERSION = 0.0.1
CFLAGS = -Wall -Wextra -Werror -std=c99

DEPS = $(shell pkg-config --cflags --libs sdl2)

all: main.c
	cc -o $(TARGET) $< $(DEPS) $(CFLAGS) -DVERSION=\"$(VERSION)\"

.PHONY: clean
clean:
	rm -f $(TARGET)