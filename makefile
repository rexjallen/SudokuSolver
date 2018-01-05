sudoku: sudoku.o draw.o
	g++ -o $@ sudoku.o draw.o

sudoku.o: sudoku.cpp
	g++ -c $<

draw.o: draw.cpp
	g++ -c $<
clean:
	rm  sudoku.o draw.o  sudoku

