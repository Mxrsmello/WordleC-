CC = g++
CFLAGS = -std=c++11

all: keyboard

keyboard: keyboard.cpp helpers.h
	$(CC) $(CFLAGS) keyboard.cpp -o keyboard

test: test.cpp helpers.h
	$(CC) $(CFLAGS) test.cpp -o test -I ../igloo-igloo.1.1.1
	clear && echo "Running all tests:" && ./test --output=color 

clean:
	rm -f keyboard
	rm -f test
