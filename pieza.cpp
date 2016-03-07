#include "pieza.hpp"
#include <iostream>
#include <cstring>
#include <ncurses.h>
using namespace std;

pieza::pieza(){

}

pieza::pieza(char Tipo, int Jugador){
	this->tipo=Tipo;
	this->jugador=Jugador;	
}

void pieza::setTipo(char Tipo){
	this->tipo=Tipo;	

}
void pieza::setJugador(int Jugador){
	this->jugador=Jugador;	
}

int pieza::getJugador(){
	return jugador;
}

char pieza::getTipo(){

	return tipo;
}
