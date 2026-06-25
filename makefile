CFLAGS = -std=c++17 -Wall -pedantic

bin/main: bin/main.o bin/game.o bin/board.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/board.o $(CFLAGS) -lncurses


bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS)

bin/board.o: src/Board.cpp src/Board.h
	mkdir -p bin	
	g++ -g -c -o bin/board.o src/Board.cpp $(CFLAGS)


bin/game.o: src/game.cpp src/game.h 
	mkdir -p bin	
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

clean:
	rm -rf *.o bin/