#ifndef PIEZA_H
#define PIEZA_H

class pieza
{
	char tipo;
	int jugador;
public:
	pieza();

	pieza(char, int);
	void setTipo(char);
	void setJugador(int);
	char getTipo();
	int getJugador();
};

	
#endif		
