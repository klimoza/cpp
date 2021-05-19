CXXFLAGS = -O2 -Wall -Werror -std=c++17

all: obj obj/huffman.o obj/main.o hw_02

hw_02: obj/huffman.o obj/main.o
	g++ obj/huffman.o obj/main.o -o hw_02

obj/main.o: src/main.cpp src/huffman.h
	g++ -c $(CXXFLAGS) src/main.cpp -o obj/main.o

obj/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c $(CXXFLAGS) src/huffman.cpp -o obj/huffman.o

test: obj obj/huffman.o obj/autotest.o hw_02_test

hw_02_test: obj/huffman.o obj/autotest.o
	g++ obj/huffman.o obj/autotest.o -o hw_02_test

obj/autotest.o: test/autotest.cpp
	g++ -c $(CXXFLAGS) test/autotest.cpp -o obj/autotest.o -I src

obj:
	mkdir -p obj

clean:
	rm -rf obj hw_02 hw_02_test

.PHONY: clean all
