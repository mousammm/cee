CC=cc

CFLAGS := -std=c89
CFLAGS += -ggdb
# CFLAGS += -Wall -Wextra -Wpedantic -Werror

EXE = cee

main: main.c
	cc $(CFLAGS) -o $(EXE) main.c

run:
	./$(EXE)

clean:
	./$(EXE)
