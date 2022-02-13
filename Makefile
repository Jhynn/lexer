FILES = src/*.c main.c
OUT = lexer
include_dirs = -Ilib
CFLAGS = $(include_dirs) -O2 -Wall

all: $(FILES)
	$(CC) $(CFLAGS) -o $(OUT) $(FILES)

clean:
	find . -iname '*~' -delete
	-rm $(OUT)
