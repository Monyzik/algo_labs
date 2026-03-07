build:
	gcc -c algorithms.c readFile.c

test: build generate
	gcc -o tests tests.c
	./tests

all:
	gcc -o main main.c
	./main

generate:
	gcc -o generator generator.c
	./generator

clean:
	rm -f *.o tests main