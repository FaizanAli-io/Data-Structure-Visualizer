all:
	g++ -Isrc/include -c main.cpp -o run/main.o
	g++ run/main.o -o run/main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
	./run/main.exe