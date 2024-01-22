TARGET = display-test
VERSION = 0.0.2

SDL2 = $(shell pkg-config --cflags --libs sdl2)
CFLAGS = -Wall -Wextra -Werror -std=c99

all: $(TARGET)

$(TARGET): main.c
	cc -o $@ $< $(SDL2) $(CFLAGS) -DVERSION=\"$(VERSION)\"

.PHONY: clean, install

install:
	@echo "Please move $(TARGET) to your PATH **manually**."
clean:
	rm -f $(TARGET)