build:
	gcc -c tree.c

test: build
	gcc -o tests tests.c
	./tests

main: build
	gcc -o main main.c
	./main

clean:
	rm -f *.o tests main