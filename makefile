Juego.exe: Ajedrez.o pieza.o
	g++ Ajedrez.o pieza.o -lncurses
Ajedrez.o:Ajedrez.cpp pieza.hpp
	g++ -c Ajedrez.cpp -lncurses
pieza.o: pieza.hpp pieza.cpp
	g++ -c pieza.cpp	
