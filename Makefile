main.exe: main.o 
	g++ main.o -o main.exe

main.o: main.cpp bstree.h
	g++ -c main.cpp -o main.o

.PHONY: clean

clean:
	rm *.exe *.o