run: main
	./main

main: main.o piece.o board.o solver.o
	g++ main.o piece.o board.o solver.o -o main

main.o:	main.cpp piece.cpp piece.h board.cpp board.h solver.h solver.o
	g++ -c -w -std=c++98 -pedantic main.cpp

piece.o: piece.cpp piece.h
	g++ -c -w -std=c++98 -pedantic piece.cpp

board.o: board.cpp board.h
	g++ -c -w -std=c++98 -pedantic board.cpp

solver.o: solver.cpp solver.h
	g++ -c -w -std=c++98 -pedantic solver.cpp

clean:
	rm *.o main