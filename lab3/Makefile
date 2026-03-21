build:
	gcc -c parse.c stack.c structures.c tree.c

test: build
	gcc -o tests tests.c
	./tests

all:
	gcc -o main main.c
	./main

clean:
	rm -f *.o tests main generator