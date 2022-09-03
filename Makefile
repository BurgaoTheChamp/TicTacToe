output: TicTacToe.o main.o
	g++ TicTacToe.o main.o -o output 

TicTacToe.o: TicTacToe.cpp
	g++ -c TicTacToe.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output