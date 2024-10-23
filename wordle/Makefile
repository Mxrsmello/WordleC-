CC = g++
CFLAGS = -std=c++11

all: wordle

wordle: wordle.cpp wordle.h
	$(CC) $(CFLAGS) wordle.cpp -o wordle

test: test.cpp wordle.h
	$(CC) $(CFLAGS) test.cpp -o test -I ../igloo-igloo.1.1.1
	clear && echo "Running all tests:" && ./test --output=color 

clean:
	rm -f wordle
	rm -f test
