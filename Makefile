CC=gcc
CFLAGS=-I .
DEPS = convert.h
OBJ = convert.o koala.o fade.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean convert

convert: $(OBJ)
	$(CC) -ggdb -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	del *.o 
	del *.exe
