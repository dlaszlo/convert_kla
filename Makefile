CC=g++
CFLAGS=-I .
DEPS = convert.h
OBJ = convert.o koala.o fade.o utils.o options.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: clean convert

convert: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o 
	rm -f convert

