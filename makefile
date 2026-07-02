CFLAGS = -std=c++17 -Wall -pedantic -Isrc

bin/main: bin/main.o bin/game.o bin/board.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/board.o $(CFLAGS) -lncurses

clean:
	rm -rf *.o bin/ test/bin/

bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/board.o: src/Board.cpp src/Board.h
	mkdir -p bin	
	g++ -g -c -o bin/board.o src/Board.cpp $(CFLAGS)

bin/game.o: src/game.cpp src/game.h 
	mkdir -p bin	
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

test/bin/board.o: test/board.cpp
	mkdir -p test/bin
	g++ -g -c -o test/bin/board.o test/board.cpp $(CFLAGS) -lgtest -lgtest_main

test: test/bin/board.o bin/board.o
	g++ -g -o bin/test test/bin/board.o bin/board.o $(CFLAGS) -lgmock -lgtest -lgtest_main
	./bin/test
