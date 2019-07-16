# simple implementation

SRCS = bench.c reverse/reverse.c
override CFLAGS += -Wall -Wextra -Ireverse -std=c99

bench: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-@rm -f bench

.PHONY: clean
