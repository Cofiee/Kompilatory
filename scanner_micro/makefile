CC = cc -Wall
OBJFile = scanner
OBJBase = \
	globals.o\
	main.o\
	scanner.o\
	symbol.o\

$(OBJFile): $(OBJBase)
	$(CC) -o $(OBJFile) $(OBJBase)

$(OBJBase): globals.h

clean:
	rm -f *.o

distclean: clean
	rm -f $(OBJFile)