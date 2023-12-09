all:
	g++ -Isrc/include -c main.cpp -o run/main.o
	g++ run/main.o -o run/main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./run/main.exe

test:
	g++ ./test.cpp -o run/test.exe
	./run/test.exe