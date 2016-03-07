#include<iostream>
#include<ncurses.h>
#include "pieza.hpp"
#include<fstream>
#include<string>
#include<cstring>
#include<string.h>
#include<sstream>
using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;
using std::string;
pieza** declarar_matriz();
char** declararMatriz();

void llenarmatriz(char** matriz);
void llenar_tablero2(pieza** temporal);
void imprimir_tablero(pieza** tablero2); 
int convertor_letras(char letra);
bool validacion_de_alfil(pieza** tablero,int i1, int j1, int i2, int j2);
bool validacion_caballo(int pos1,int pos2,int pos3,int pos4, pieza** tablero);
bool validacion_torre(int i1, int j1, int i2, int j2, pieza** tablero);
bool validacion_peon(pieza** tablero, int pos1,int pos2,int pos3, int pos4, int jugador);
bool validacion_rey(pieza** tablero,int pos1,int pos2,int pos3,int pos4);
bool hacke(int jugador,pieza** tablero,int posicion1,int posicion2);
bool hacke_mate(pieza** tablero, int jugador);
void salvar(string posiciones);
void mover(int pos1,int pos2,int pos3,int pos4,pieza** tablero2);
bool llegar(int jugador, pieza** tablero,int posicion1,int posicion2);
bool llegar2(int jugador, pieza** tablero,int posicion1,int posicion2);
int main(int argc, char*argv[]){
	initscr();		
	start_color();
	int posicion_de_rey1=0;
	int posicion_de_rey2=0;
	init_pair(1,COLOR_BLACK, COLOR_BLACK);
        init_pair(2,COLOR_GREEN, COLOR_GREEN);
	init_pair(3,COLOR_RED, COLOR_RED);
	init_pair(4,COLOR_CYAN, COLOR_CYAN);
	init_pair(5,COLOR_WHITE, COLOR_WHITE);
	init_pair(6,COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(7,COLOR_BLUE, COLOR_BLUE);
	init_pair(8,COLOR_YELLOW,COLOR_YELLOW); 
	init_pair(9,COLOR_WHITE,COLOR_BLACK);
	init_pair(10,COLOR_BLACK,COLOR_WHITE);
	
	char** tablero=declararMatriz();
	pieza** tablero2=declarar_matriz();
	llenar_tablero2(tablero2);
	int bandera=0;
	int bandera2=0;
	char seguirjugando=' ';
	int jugador=1;
	bool val1=false;
	bool val2=false;
	bool val3=false;
	bool val4=false;	
	int  control=0;
	char direccion=' ';
	int contador_de_entrada=0;
	int opcion_principal=' ';
	int pos1,pos2,pos3,pos4;
	char coordenadas[4];
	char tipo_antiguo,tipo_nuevo;
	int  jugador_antiguo,jugador_nuevo;
	mvprintw(21,60,"1. Jugar Ajedrez ");
	mvprintw(22,60,"2. cargar partida anterior Ajedrez ");
	mvprintw(23,60,"3. guardar partida Ajedrez ");
	mvprintw(24,60,"4. salir  ");
	
	opcion_principal=getch();
	clear();
	refresh();
	
	while(opcion_principal != '4'){
		if(opcion_principal=='1'){
			imprimir_tablero(tablero2);	
			while(seguirjugando !='1'){
				if(jugador==1){
					string copiajugador1=" ";
					
					mvprintw(5,100,"**************** Jugador1************ ");	
					for(int x=0;x<8;x++){
						for(int y=0;y<8;y++){
							if(tablero2[x][y].getTipo()=='K' && tablero2[x][y].getJugador() == jugador){
		 						posicion_de_rey1=x;
								posicion_de_rey2=y;
				
							}
						}			
					}
					if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
						mvprintw(6,105,"hacke");
						 if(hacke_mate(tablero2,jugador)==true){
							mvprintw(8,105,"HackeMate presione enter");
							getch();
							llenar_tablero2(tablero2);
							opcion_principal='3';
							break;
						}			
					}
					mvprintw(20,98,"Ingrese sus coordenadas :  ");
					while(contador_de_entrada < 4){
						noecho();
						char temp;
						temp = getch();
						if(control==0){							
							if((temp >= 65 && temp<=72)){
								echo();
								addch(temp);
								coordenadas[contador_de_entrada] = temp;
								contador_de_entrada++;
								control=1;
							}
						}else{
							if((temp >= 49 && temp<=56)){
								echo();
								addch(temp);
								coordenadas[contador_de_entrada] = temp;
								contador_de_entrada++;
								control=0;
							}
						}
					}
						
					pos1= convertor_letras(coordenadas[0]);
					pos2= convertor_letras(coordenadas[1]);
					pos3= convertor_letras(coordenadas[2]);
					pos4= convertor_letras(coordenadas[3]);
					control=0;
					contador_de_entrada=0;
			
					if(tablero2[pos1][pos2].getJugador()==1){
						if(tablero2[pos1][pos2].getTipo()=='A'){
							if( validacion_de_alfil( tablero2,pos1,pos2,pos3,pos4)==true){
								mover( pos1, pos2, pos3,pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
								}
							}
						
					
						}else if(tablero2[pos1][pos2].getTipo()=='C'){
							if( validacion_caballo( pos1, pos2, pos3, pos4,tablero2)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
								}
							}
						}else if(tablero2[pos1][pos2].getTipo()=='T'){
							if( validacion_torre( pos1, pos2, pos3, pos4,tablero2)==true){
								mover( pos1, pos2, pos3, pos4,tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
								}
							}
							
						}else if(tablero2[pos1][pos2].getTipo()=='Q'){
							if( validacion_torre( pos1, pos2, pos3, pos4,tablero2)==true || validacion_de_alfil(tablero2,pos1,pos2,pos3,pos4)== true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
								}
					
							}
						}else if(tablero2[pos1][pos2].getTipo()=='K'){
							if(validacion_rey( tablero2,pos1, pos2, pos3, pos4)==true){					
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
									if(pos3==7){
										tablero2[pos3][pos4].setTipo('Q');												
									}	
								}
							}
						}else if(tablero2[pos1][pos2].getTipo()=='P'){
							if(validacion_peon(tablero2,pos1,pos2,pos3,pos4,jugador)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=2;
								}					
							}				
						}
					}
					
					clear();
					refresh();
					imprimir_tablero(tablero2);
			
				}else{
					
					mvprintw(5,100,"**************** Jugador2************ ");
						
					for(int x=0;x<8;x++){
						for(int y=0;y<8;y++){
							if(tablero2[x][y].getTipo()=='K' && tablero2[x][y].getJugador() == jugador){
		 						posicion_de_rey1=x;
								posicion_de_rey2=y;
				
							}
						}			
					}
					if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
						mvprintw(6,105,"Hacke");
						 if(hacke_mate(tablero2,jugador)==true){
							mvprintw(8,105,"HackeMate presione enter");
							getch();
							llenar_tablero2(tablero2);
							opcion_principal='3';
							break;
						}			
					}
					mvprintw(20,98,"Ingrese sus coordenadas :  ");
					while(contador_de_entrada < 4){
						noecho();
						char temp;
						temp = getch();
						if(control==0){							
							if((temp >= 65 && temp<=72)){
								echo();
								addch(temp);
								coordenadas[contador_de_entrada] = temp;
								contador_de_entrada++;
								control=1;
							}
						}else{
							if((temp >= 49 && temp<=57)){
								echo();
								addch(temp);
								coordenadas[contador_de_entrada] = temp;
								contador_de_entrada++;
								control=0;
							}
						}
					}
				
			
					pos1= convertor_letras(coordenadas[0]);
					pos2= convertor_letras(coordenadas[1]);
					pos3= convertor_letras(coordenadas[2]);
					pos4= convertor_letras(coordenadas[3]);
					control=0;
					contador_de_entrada=0;
					if(tablero2[pos1][pos2].getJugador()==2){
						if(tablero2[pos1][pos2].getTipo()=='A'){
							if( validacion_de_alfil( tablero2,pos1,pos2,pos3,pos4)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								
								jugador=1;
							}
					
						}else if(tablero2[pos1][pos2].getTipo()=='C'){
							if( validacion_caballo( pos1, pos2, pos3, pos4,tablero2)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=1;
								}
							}
						}else if(tablero2[pos1][pos2].getTipo()=='T'){
							if( validacion_torre( pos1, pos2, pos3, pos4,tablero2)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
							if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=1;
								}
							}
						}else if(tablero2[pos1][pos2].getTipo()=='Q'){
							if( validacion_torre( pos1, pos2, pos3, pos4,tablero2)==true || validacion_de_alfil(tablero2,pos1,pos2,pos3,pos4)== true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=1;
								}
					
							}
						}else if(tablero2[pos1][pos2].getTipo()=='K'){
							if(validacion_rey( tablero2,pos1, pos2, pos3, pos4)==true){					
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									jugador=1;
								}
							}
						}else if(tablero2[pos1][pos2].getTipo()=='P'){
							if(validacion_peon(tablero2,pos1,pos2,pos3,pos4,jugador)==true){
								mover( pos1, pos2, pos3, pos4, tablero2);
								if(hacke(jugador,tablero2,posicion_de_rey1,posicion_de_rey2)==true){
									mover( pos3, pos4, pos1,pos2, tablero2);
									 		
								}else{
									if(pos3==0){
										tablero2[pos3][pos4].setTipo('Q');												
									}	
									jugador=1;
								}				
							}				
						}
					}
	
					clear();
					refresh();
					imprimir_tablero(tablero2);
			
				}
		
				mvprintw(22,100,"si desea seguir jugando; ");
				mvprintw(23,100," presione cualquier numero o letra menos 1");
				seguirjugando=getch();
		
			}
		}
		if(opcion_principal=='3'){
			stringstream palabra_aguardar;
			
			for(int x=0;x<8;x++){
				for(int y=0;y<8;y++){
					if(tablero2[x][y].getTipo()=='T' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"a";		
					}
					if(tablero2[x][y].getTipo()=='C' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"b";		
					}  
					if(tablero2[x][y].getTipo()=='A' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"c";		
					} 
					if(tablero2[x][y].getTipo()=='Q' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"d";		
					}   
					if(tablero2[x][y].getTipo()=='K' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"e";		
					}  
					if(tablero2[x][y].getTipo()==' ' && tablero2[x][y].getJugador()==0){
						palabra_aguardar<<"f";		
					}  
					if(tablero2[x][y].getTipo()=='T' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"g";		
					}
					if(tablero2[x][y].getTipo()=='C' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"h";		
					}  
					if(tablero2[x][y].getTipo()=='A' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"i";		
					} 
					if(tablero2[x][y].getTipo()=='Q' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"j";		
					}   
					if(tablero2[x][y].getTipo()=='K' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"k";		
					}  
					if(tablero2[x][y].getTipo()=='P' && tablero2[x][y].getJugador()==1){
						palabra_aguardar<<"l";		
					}  
					if(tablero2[x][y].getTipo()=='P' && tablero2[x][y].getJugador()==2){
						palabra_aguardar<<"m";		
					}  
				}	
			
			}	
				
			salvar(palabra_aguardar.str());	
		}
		if(opcion_principal=='2'){
			char cadena[65];
			cadena[64]='\0';
			ifstream fentrada("juego.txt");
			for(int x=0; x<64;x++){
				cadena[x]=fentrada.get();	
			}
			fentrada.close();
			int pos=0;
			for(int x=0;x<8;x++){
				for(int y=0;y<8;y++){
					if(cadena[pos]=='a'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('T');
					}
					if(cadena[pos]=='b'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('C');
					}
					if(cadena[pos]=='c'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('A');
					}
					if(cadena[pos]=='d'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('Q');
					}
					if(cadena[pos]=='e'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('K');
					}
					if(cadena[pos]=='f'){
						tablero2[x][y].setJugador(0);
						tablero2[x][y].setTipo(' ');
					}
					if(cadena[pos]=='g'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('T');
					}
					if(cadena[pos]=='h'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('C');
					}
					if(cadena[pos]=='i'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('A');
					}
					if(cadena[pos]=='j'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('Q');
					}
					if(cadena[pos]=='k'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('K');
					}
					if(cadena[pos]=='l'){
						tablero2[x][y].setJugador(1);
						tablero2[x][y].setTipo('P');
					}
					if(cadena[pos]=='m'){
						tablero2[x][y].setJugador(2);
						tablero2[x][y].setTipo('P');
					}
					pos++;
				}
			}
			
		}
		clear();
		refresh();
		seguirjugando ='0';
		mvprintw(21,60,"1. Jugar Ajedrez ");
		mvprintw(22,60,"2. cargar partida anterior Ajedrez ");
		mvprintw(23,60,"3. guardar partida Ajedrez ");
		mvprintw(24,60,"4. salir ");
		mvprintw(25,60," ");
		opcion_principal=getch();
		clear();
		refresh();
		
	}
	endwin();	
	return 0;
	
}


char** declararMatriz(){
	char** h=new char*[8];
	
	for(int i = 0; i<8; i++){
		h[i]= new char[8];		
	}
	return h;	
}

pieza** declarar_matriz(){
	pieza** temp=new pieza*[8];
	
	for(int i = 0; i<8; i++){
		temp[i]= new pieza[8];		
	}
	return temp;	
}

void llenarmatriz(char** matriz){
	for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                        matriz[i][j]=' ';
                }
        }
	
	
}

void llenar_tablero2(pieza** tablero){
	for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                       if (i>1 &&i<6){
				tablero[i][j].setTipo(' ');
				tablero[i][j].setJugador(0);			
			}
			if(i==1){
				tablero[i][j].setTipo('P');
				tablero[i][j].setJugador(1);			
			}
			if(i==6){
				tablero[i][j].setTipo('P');
				tablero[i][j].setJugador(2);			
			}
                }
        }
	tablero[0][0].setTipo('T');		
	tablero[0][7].setTipo('T');
        tablero[7][7].setTipo('T');
        tablero[7][0].setTipo('T');
        tablero[0][1].setTipo('C');		
	tablero[0][6].setTipo('C');
        tablero[7][1].setTipo('C');
        tablero[7][6].setTipo('C');
	tablero[0][2].setTipo('A');		
	tablero[0][5].setTipo('A');
	tablero[7][2].setTipo('A');		
	tablero[7][5].setTipo('A');
	tablero[0][3].setTipo('Q');	
	tablero[0][4].setTipo('K');
	tablero[7][3].setTipo('K');
	tablero[7][4].setTipo('Q');
	



	tablero[0][0].setJugador(1);		
	tablero[0][7].setJugador(1);
        tablero[7][7].setJugador(2);
        tablero[7][0].setJugador(2);
        tablero[0][1].setJugador(1);		
	tablero[0][6].setJugador(1);
        tablero[7][1].setJugador(2);
        tablero[7][6].setJugador(2);
	tablero[0][2].setJugador(1);		
	tablero[0][5].setJugador(1);
	tablero[7][2].setJugador(2);		
	tablero[7][5].setJugador(2);
	tablero[0][3].setJugador(1);	
	tablero[0][4].setJugador(1);
	tablero[7][3].setJugador(2);
	tablero[7][4].setJugador(2);
	
	


} 
void imprimir_tablero(pieza** tablero2){
	int bandera=0;
	int bandera2=0;
			
	start_color();
	init_pair(1,COLOR_BLACK, COLOR_BLACK);
        init_pair(2,COLOR_GREEN, COLOR_GREEN);
	init_pair(3,COLOR_RED, COLOR_RED);
	init_pair(4,COLOR_CYAN, COLOR_CYAN);
	init_pair(5,COLOR_WHITE, COLOR_WHITE);
	init_pair(6,COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(7,COLOR_BLUE, COLOR_BLUE);
	init_pair(8,COLOR_YELLOW,COLOR_YELLOW); 
	init_pair(9,COLOR_WHITE,COLOR_BLACK);
	init_pair(10,COLOR_BLACK,COLOR_WHITE);
	printw("      1           2           3           4          5            6            7           8     ");
	printw("\n");
	for(int x=0;x<8;x++){
			for(int p=0;p<5;p++){
				for(int q=0;q<8;q++){

					if(bandera==0){
						if(p==3){
							attron(COLOR_PAIR(2));	
							printw("     ");
							attroff(COLOR_PAIR(2));
							if(tablero2[x][q].getJugador()==1){
								attron(COLOR_PAIR(9));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(9));
							}
							if(tablero2[x][q].getJugador()==2){
								attron(COLOR_PAIR(10));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(10));
							}
							if(tablero2[x][q].getJugador()==0){
								attron(COLOR_PAIR(2));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(2));	
							}
							attron(COLOR_PAIR(2));	
							printw("      ");
							attroff(COLOR_PAIR(2));
						}else{
							attron(COLOR_PAIR(2));
							printw("            ");
							attroff(COLOR_PAIR(2));
						}
						attron(COLOR_PAIR(10));
							
						if(p==3 && q==7 && x==0){
							printw("A");
						}
						if(p==3 && q==7 && x==1){
							printw("B");
						}
						if(p==3 && q==7 && x==2){
							printw("C");
						}
						if(p==3 && q==7 && x==3){
							printw("D");
						}
						if(p==3 && q==7 && x==4){
							printw("E");
						}
						if(p==3 && q==7 && x==5){
							printw("F");
						}
						if(p==3 && q==7 && x==6){
							printw("G");
						}
						if(p==3 && q==7 && x==7){
							printw("H");
						}
						attroff(COLOR_PAIR(10));	
					}
					if(bandera==1){
						if(p==3){
							attron(COLOR_PAIR(1));	
							printw("     ");
							attroff(COLOR_PAIR(1));
							if(tablero2[x][q].getJugador()==1){
								attron(COLOR_PAIR(9));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(9));
							}
							if(tablero2[x][q].getJugador()==2){
								attron(COLOR_PAIR(10));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(10));
							}
							if(tablero2[x][q].getJugador()==0){
								attron(COLOR_PAIR(1));
								addch(tablero2[x][q].getTipo());
								attroff(COLOR_PAIR(1));	
							}
								
							attron(COLOR_PAIR(1));	
							printw("      ");
							attroff(COLOR_PAIR(1));
						}else{
							attron(COLOR_PAIR(1));
							printw("            ");
							attroff(COLOR_PAIR(1));
						}
						attron(COLOR_PAIR(10));
							
						if(p==3 && q==7 && x==0){
							printw("A");
						}
						if(p==3 && q==7 && x==1){
							printw("B");
						}
						if(p==3 && q==7 && x==2){
							printw("C");
						}
						if(p==3 && q==7 && x==3){
							printw("D");
						}
						if(p==3 && q==7 && x==4){
							printw("E");
						}
						if(p==3 && q==7 && x==5){
							printw("F");
						}
						if(p==3 && q==7 && x==6){
							printw("G");
						}
						if(p==3 && q==7 && x==7){
							printw("H");
						}
						attroff(COLOR_PAIR(10));
						
					}	
					if(bandera==0){
						bandera=1;
					}else{		
					
						bandera=0;
					}
				}
				printw("\n");			
			}
			if(bandera==0){
				bandera=1;
			}else{
				bandera=0;
			}
			

		}
	
	


}

int convertor_letras(char letra){

	if(letra=='A'){
		return 0;
	}	
	if(letra=='B'){
		return 1;
	}
	if(letra=='C'){
		return 2;
	}
	if(letra=='D'){
		return 3;
	}
	if(letra=='E'){
		return 4;
	}
	if(letra=='F'){
		return 5;
	}
	if(letra=='G'){
		return 6;
	}
	if(letra=='H'){
		return 7;
	}
	if(letra=='1'){
		return 0;
	}	
	if(letra=='2'){
		return 1;
	}
	if(letra=='3'){
		return 2;
	}
	if(letra=='4'){
		return 3;
	}
	if(letra=='5'){
		return 4;
	}
	if(letra=='6'){
		return 5;
	}
	if(letra=='7'){
		return 6;
	}
	if(letra=='8'){
		return 7;
	}
}

bool validacion_de_alfil(pieza** tablero,int i1, int j1, int i2, int j2){
	int constantei=i1;
	int constantej=j1;
	bool pieza_enmedio=true;
	bool movimiento1=false;
	bool movimiento2=false;
	bool movimiento3=false;
	bool movimiento4=false;	
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1+1;
		j1=j1-1;		
		if(i1==i2 && j1==j2){
			movimiento1=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1+1;
		j1=j1+1;		
		if(i1==i2 && j1==j2){
			movimiento2=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1-1;
		j1=j1+1;		
		if(i1==i2 && j1==j2){
			movimiento3=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1-1;
		j1=j1-1;		
		if(i1==i2 && j1==j2){
			movimiento4=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
//*++++++++++++++++++++++++++++++++++++++++++++++++++++validacion pieza en medio
	if(movimiento1==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
				
			i1=i1+1;
			j1=j1-1;		
			
			if(tablero[i1][j1].getTipo()==' '){
					if(i1==i2 && j1==j2){
						break;					
					}
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
		
		}
	
	}
	i1=constantei;
	j1=constantej;
	if(movimiento2==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
					
			i1=i1+1;
			j1=j1+1;		
			
			if(tablero[i1][j1].getTipo()==' '){
					if(i1==i2 && j1==j2){
						break;					
					}
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if(movimiento3==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
			
			i1=i1-1;
			j1=j1+1;		
			if(tablero[i1][j1].getTipo()==' '){
				if(i1==i2 && j1==j2){
					break;					
				}	
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if(movimiento4==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
						
			i1=i1-1;
			j1=j1-1;		
			if(tablero[i1][j1].getTipo()==' '){
				if(i1==i2 && j1==j2){
					break;					
				}	
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if((movimiento1==true || movimiento2==true || movimiento3==true || movimiento4==true) && pieza_enmedio==true){
		return true;
	}else{
		return false;	
	}		

}

bool validacion_caballo(int pos1,int pos2,int pos3,int pos4, pieza** tablero){
	bool movimiento1=false;
	bool movimiento2=false;
	bool movimiento3=false;
	bool movimiento4=false;
	bool movimiento5=false;
	bool movimiento6=false;
	bool movimiento7=false;
	bool movimiento8=false;
	bool pieza_puesta=false;
	if(((pos1-2)==pos3 && (pos2+1)==pos4)){
		movimiento1=true;	
	}
		
	if(((pos1-1)==pos3 && (pos2+2)==pos4)){
		movimiento2=true;	
	}
	
	if(((pos1+1)==pos3 && (pos2+2)==pos4)){
		movimiento3=true;	
	} 
 
	if(((pos1+2)==pos3 && (pos2+1)==pos4)){
		movimiento4=true;	
	} 
	if(((pos1+2)==pos3 && (pos2-1)==pos4)){
		movimiento5=true;	
	} 
	if(((pos1+1)==pos3 && (pos2-2)==pos4)){
		movimiento6=true;	
	} 
	if(((pos1-1)==pos3 && (pos2-2)==pos4)){
		movimiento7=true;
	}	 
	if(((pos1-2)==pos3 && (pos2-1)==pos4)){
		movimiento8=true;	
	}
				
//*****************************************************************
	if(movimiento1==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	
	if(movimiento2==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	
	if(movimiento3==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}
	if(movimiento4==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}
	if(movimiento5==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	
	if(movimiento6==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	
	if(movimiento7==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	
	if(movimiento8==true){
		if(tablero[pos3][pos4].getJugador()!=tablero[pos1][pos2].getJugador()){
			pieza_puesta=true;
		} 
	}	


	if((movimiento1==true || movimiento2==true || movimiento3==true || movimiento4==true || movimiento5==true || movimiento6==true || movimiento7==true || movimiento8==true) && pieza_puesta==true){
		return true;	
	}else{
		return false;	
	}		
}


bool validacion_torre(int i1, int j1, int i2, int j2, pieza** tablero){
	int constantei=i1;
	int constantej=j1;
	bool pieza_enmedio=true;
	bool movimiento1=false;
	bool movimiento2=false;
	bool movimiento3=false;
	bool movimiento4=false;	
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		
		j1=j1+1;		
		if(i1==i2 && j1==j2){
			movimiento1=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1+1;
				
		if(i1==i2 && j1==j2){
			movimiento2=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		
		j1=j1-1;		
		if(i1==i2 && j1==j2){
			movimiento3=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
	while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
		i1=i1-1;
				
		if(i1==i2 && j1==j2){
			movimiento4=true;
		}
	
	}
	i1=constantei;
	j1=constantej;
//********************************************************************************************************+
	if(movimiento1==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
			
			j1=j1+1;		
			
			if(tablero[i1][j1].getTipo()==' '){
				if(i1==i2 && j1==j2){
						break;					
				}	
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
			
		}
	
	}
	i1=constantei;
	j1=constantej;
	if(movimiento2==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
				
			i1=i1+1;
					
			if(tablero[i1][j1].getTipo()==' '){
					if(i1==i2 && j1==j2){
						break;					
					}
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if(movimiento3==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
			
			
			j1=j1-1;		
			if(tablero[i1][j1].getTipo()==' '){
					if(i1==i2 && j1==j2){
						break;					
					}
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if(movimiento4==true){
		while(i1>=0 && j1>=0 && i1<=8 && j1<=8){
			
			i1=i1-1;
					
			if(tablero[i1][j1].getTipo()==' ' ){
					if(i1==i2 && j1==j2){
						break;					
					}
			}else{
				if(  tablero[i1][j1].getJugador() != tablero[constantei][constantej].getJugador() && i1 == i2 && j1 ==j2){
					pieza_enmedio=true;					
					break;
				}else{	
					pieza_enmedio=false;
					break;
				}				
			}	
	
		}
	}
	i1=constantei;
	j1=constantej;
	if((movimiento1==true || movimiento2==true || movimiento3==true || movimiento4==true) && pieza_enmedio==true){
		return true;
	}else{
		return false;	
	}		
		
}




bool validacion_rey(pieza** tablero,int pos1,int pos2,int pos3,int pos4){
	bool movimiento1=false;
	bool movimiento2=false;
	bool movimiento3=false;
	bool movimiento4=false;
	bool movimiento5=false;
	bool movimiento6=false;
	bool movimiento7=false;
	bool movimiento8=false;
	bool pieza_enmedio=false;
	if(pos1-1==pos3 && pos2==pos4){
		movimiento1=true;
		if(movimiento1==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1-1==pos3 && pos2+1==pos4){
		movimiento2=true;
		if(movimiento2==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1==pos3 && pos2+1==pos4){
		movimiento3=true;
		if(movimiento3==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1+1==pos3 && pos2+1==pos4){
		movimiento4=true;
		if(movimiento4==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1+1==pos3 && pos2==pos4){
		movimiento5=true;
		if(movimiento5==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1+1==pos3 && pos2-1==pos4){
		movimiento6=true;
		if(movimiento6==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}		
	if(pos1==pos3 && pos2-1==pos4){
		movimiento7=true;
		if(movimiento7==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}
	if(pos1-1==pos3 && pos2-1==pos4){
		movimiento8=true;
		if(movimiento8==true){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador()){
				pieza_enmedio=true;			
			}					
		}
	}
	if((movimiento1==true || movimiento2==true || movimiento3== true || movimiento4==true || movimiento5==true || movimiento6==true || movimiento7==true || movimiento8==true)	&& pieza_enmedio==true){
		
	}			


}

bool hacke(int jugador, pieza** tablero,int posicion1,int posicion2){
	
	
	int cuantas_en_jaque=0;
	
	
	
	mvprintw(2,102,"la posi es" + posicion1);
	
	int copiadepo1=posicion1;
	int copiadepo2=posicion2;	
	int valida=0;
	valida=1;
	posicion1=posicion1+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					cuantas_en_jaque++;
										
					break;
			}else{	
					
					break;
			}				
		}
		posicion1=posicion1+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	
	posicion1=posicion1-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					cuantas_en_jaque++;
										
					break;
			}else{	
					
					break;
			}				
		}	
		posicion1=posicion1-1;
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					cuantas_en_jaque++;
										
					break;
			}else{	
				
					break;
			}				
		}
		posicion2=posicion2+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					cuantas_en_jaque++;
										
					break;
			}else{	
					
					break;
			}				
		}
		posicion2=posicion2-1;
			  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;

//****************************************************************************************
	valida=1;
	posicion1=posicion1+1;
	posicion2=posicion2+1;
	int cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==1){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
					
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==2){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						
						cuantas_en_jaque++;
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		
		posicion1=posicion1+1;
		posicion2=posicion2+1;		
		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion1=posicion1-1;
	posicion2=posicion2+1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==2){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==1){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						
						cuantas_en_jaque++;
											
						break;
				}else{	
						
						break;
				}				
			}			
			
		}
		posicion1=posicion1-1;
		posicion2=posicion2+1;		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion1=posicion1-1;
	posicion2=posicion2-1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==2){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==1){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						
						cuantas_en_jaque++;
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		posicion1=posicion1-1;
		posicion2=posicion2-1;		
	}

	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	int h=7;
	posicion1=posicion1+1;
	posicion2=posicion2-1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==1){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						
						cuantas_en_jaque++;
											
						break;
					}else{
						break;
					}	
				}
			}
			if(jugador==2){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						
						cuantas_en_jaque++;
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		posicion1=posicion1+1;
		posicion2=posicion2-1;		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	int pos1=posicion1;
	int pos2=posicion2;



	if(((pos1-2)>=0 && (pos1-2)<8)  && ((pos2+1)>=0 && (pos2+1)<8)){
			if(tablero[pos1-2][pos2+1].getTipo()=='C' && tablero[pos1-2][pos2+1].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}
	}
		
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1-1][pos2+2].getTipo()=='C' && tablero[pos1-1][pos2+2].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}	
	}
	
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1+1][pos2+2].getTipo()=='C' && tablero[pos1+1][pos2+2].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}
	} 
 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2+1)>=0 && (pos2+1)<8)){
		if(tablero[pos1+2][pos2+1].getTipo()=='C' && tablero[pos1+2][pos2+1].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}
	} 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1+2][pos2-1].getTipo()=='C' && tablero[pos1+2][pos2-1].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}	
	} 
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1+1][pos2-2].getTipo()=='C' && tablero[pos1+1][pos2-2].getJugador() !=jugador){ 		
				cuantas_en_jaque++;
			}
	} 
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1-1][pos2-2].getTipo()=='C' && tablero[pos1-1][pos2-2].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}
	}	 
	if(((pos1-2)>=0 && (pos1-2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1-2][pos2-1].getTipo()=='C' && tablero[pos1-2][pos2-1].getJugador() !=jugador){ 		
				cuantas_en_jaque++;	
			}	
	}
	
	
	if(cuantas_en_jaque>0 ){
		return true;
	}else{
		return false;
	} 
	
}


bool validacion_peon(pieza** tablero, int pos1,int pos2,int pos3, int pos4, int jugador){
	bool validacion= false;
	if(jugador==1){
		if((pos2==pos4) && (pos1+1==pos3)){
				if(tablero[pos3][pos4].getTipo()==' '){
					validacion=true;			
				}	
		}
		if((pos2==pos4) && (pos1+2==pos3)  && (pos1==1)){
				if(tablero[pos3][pos4].getTipo()==' '){
					validacion=true;			
				}	
		}
		if((pos4==pos2+1 && pos3==pos1+1) || (pos4==pos2-1 && pos3==pos1+1)){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador() &&  tablero[pos3][pos4].getJugador() !=0){
				validacion=true;			
			}	
		}
	}else{
		if((pos2==pos4) && (pos1-1==pos3 || pos1-2==pos3 )){
				if(tablero[pos3][pos4].getTipo()==' '){
					validacion=true;			
				}	
		}
		if((pos4==pos2-1 && pos3==pos1-1) || (pos4==pos2+1 && pos3==pos1-1) ){
			if(tablero[pos3][pos4].getJugador() != tablero[pos1][pos2].getJugador() &&  tablero[pos3][pos4].getJugador() !=0){
				validacion=true;			
			}	
		}
		if((pos2==pos4) && (pos1-2==pos3)  && (pos1==6)){
				if(tablero[pos3][pos4].getTipo()==' '){
					validacion=true;			
				}	
		}	
	}
	return validacion;
} 

bool hacke_mate(pieza** tablero, int jugador){
	int posicion1=0;
	int posicion2=0;
	int pos1=0;
	int pos2=0;
	int lugar_movible=0;
	int lugar_con_hacke=0;
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			if(tablero[x][y].getTipo()=='K' && tablero[x][y].getJugador() == jugador){
 				pos1=x;
				pos2=y;
		
			}
		}			
	}	
	int copiadepo1=pos1;
	int copiadepo2=pos2;
	int valida=0;
	if(pos1-1>=0 && pos1-1<8 && pos2>=0 && pos2<8){		
			if(tablero[pos1-1][pos2].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1-1,pos2)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1-1>=0 && pos1-1<8 && pos2-1>=0 && pos2-1<8){		
			if(tablero[pos1-1][pos2-1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1-1,pos2-1)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1-1>=0 && pos1-1<8 && pos2+1>=0 && pos2+1<8){		
			if(tablero[pos1-1][pos2+1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1-1,pos2+1)==true){
					lugar_con_hacke++;				
				}		
			}					
	}						
	if(pos1>=0 && pos1<8 && pos2-1>=0 && pos2-1<8){		
			if(tablero[pos1][pos2-1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1,pos2-1)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1>=0 && pos1<8 && pos2+1>=0 && pos2+1<8){		
			if(tablero[pos1][pos2+1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1,pos2+1)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1+1>=0 && pos1+1<8 && pos2-1>=0 && pos2-1<8){		
			if(tablero[pos1+1][pos2-1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1+1,pos2-1)==true){
					
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1+1>=0 && pos1+1<8 && pos2>=0 && pos2<8){		
			if(tablero[pos1+1][pos2].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1+1,pos2)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
	if(pos1+1>=0 && pos1+1<8 && pos2+1>=0 && pos2+1<8){		
			if(tablero[pos1+1][pos2+1].getJugador() != jugador){
				lugar_movible++;				
				if(hacke(jugador,tablero,pos1+1,pos2+1)==true){
					lugar_con_hacke++;				
				}		
			}					
	}
//*************************************************************************************
	int cuantas_en_jaque=0;
	int enjaque=0;
	int cambio=0;
	if(jugador==1){
		cambio=2;
	}else{
		cambio=1;
	}	
	posicion1=posicion1+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){	
		if(tablero[posicion1][posicion2].getTipo()==' '){									
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}					
					break;
			}else{	
					
					break;
			}				
		}
		posicion1=posicion1+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;	
	posicion1=posicion1-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
				enjaque++;
				if(hacke(cambio,tablero,posicion1,posicion2)==true){
					cuantas_en_jaque++;
				}					
				break;						
			}else{	
					
					break;
			}				
		}	
		posicion1=posicion1-1;
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
									
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
				enjaque++;
				if(hacke(cambio,tablero,posicion1,posicion2)==true){
					cuantas_en_jaque++;
				}	
										
				break;
			}else{	
				
					break;
			}				
		}
		posicion2=posicion2+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
										
					break;
			}else{	
					
					break;
			}				
		}
		posicion2=posicion2-1;
			  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;

//****************************************************************************************
	int comida=0;
	posicion1=posicion1+1;
	posicion2=posicion2+1;
	int cont1=0;
	
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==1){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						
					enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
					
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						enjaque++;
						if(hacke(cambio,tablero,posicion1,posicion2)==true){
							cuantas_en_jaque++;
						}	
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==2){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		
		posicion1=posicion1+1;
		posicion2=posicion2+1;		
		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
		posicion1=posicion1-1;
		posicion2=posicion2+1;
		cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==2){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}			
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==1){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
					enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
				}else{	
						
						break;
				}				
			}			
			
		}
		posicion1=posicion1-1;
		posicion2=posicion2+1;		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion1=posicion1-1;
	posicion2=posicion2-1;
		cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2-valida>=0 && posicion2-valida<8){
		
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==2){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==1){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						
						cuantas_en_jaque++;
					}	
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		posicion1=posicion1-1;
		posicion2=posicion2-1;		
	}

	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	int h=7;
	posicion1=posicion1+1;
	posicion2=posicion2-1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(jugador==1){
				if(cont1==1){
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q' || tablero[posicion1][posicion2].getTipo()=='P') ){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
						
						break;
					}	
				}else{
					if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q') ){
						enjaque++;
						
					if(hacke(tablero[posicion1][posicion2].getJugador(),tablero,posicion1,posicion2)==true){
													
						cuantas_en_jaque++;
					}	
											
						break;
					}else{	
						
						break;
					}	
				}
			}
			if(jugador==2){
				if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
						enjaque++;
					if(hacke(cambio,tablero,posicion1,posicion2)==true){
						cuantas_en_jaque++;
					}	
											
						break;
				}else{	
						
						break;
				}				
			}			
		}
		posicion1=posicion1+1;
		posicion2=posicion2-1;		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	 pos1=posicion1;
	 pos2=posicion2;



	if(((pos1-2)>=0 && (pos1-2)<8)  && ((pos2+1)>=0 && (pos2+1)<8)){
			if(tablero[pos1-2][pos2+1].getTipo()=='C' && tablero[pos1-2][pos2+1].getJugador() !=jugador){ 		
					enjaque++;
					if(hacke(cambio,tablero,pos1-2,pos2+1)==true){
						cuantas_en_jaque++;
					}	
			}
	}
		
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1-1][pos2+2].getTipo()=='C' && tablero[pos1-1][pos2+2].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1-1,pos2+2)==true){
						cuantas_en_jaque++;
					}		
			}	
	}
	
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1+1][pos2+2].getTipo()=='C' && tablero[pos1+1][pos2+2].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1+1,pos2+2)==true){
						cuantas_en_jaque++;
					}		
			}
	} 
 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2+1)>=0 && (pos2+1)<8)){
		if(tablero[pos1+2][pos2+1].getTipo()=='C' && tablero[pos1+2][pos2+1].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1+2,pos2+1)==true){
						cuantas_en_jaque++;
					}		
			}
	} 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1+2][pos2-1].getTipo()=='C' && tablero[pos1+2][pos2-1].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1+2,pos2-1)==true){
						cuantas_en_jaque++;
					}		
			}	
	} 
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1+1][pos2-2].getTipo()=='C' && tablero[pos1+1][pos2-2].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1+1,pos2-2)==true){
						cuantas_en_jaque++;
					}	
			}
	} 
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1-1][pos2-2].getTipo()=='C' && tablero[pos1-1][pos2-2].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1-1,pos2-2)==true){
						cuantas_en_jaque++;
					}
			}
	}	 
	if(((pos1-2)>=0 && (pos1-2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1-2][pos2-1].getTipo()=='C' && tablero[pos1-2][pos2-1].getJugador() !=jugador){ 		
				enjaque++;
					if(hacke(cambio,tablero,pos1-2,pos2-1)==true){
						cuantas_en_jaque++;
					}		
			}	
	}
			
//******************************************************************************++++++++	
	if(lugar_movible==lugar_con_hacke && lugar_movible !=0 && enjaque != cuantas_en_jaque && llegar( jugador,tablero, posicion1,posicion2)==true){
		return true;
	}else{
		return false;	
	}		
	//llegar( jugador,tablero, posicion1,posicion2)

}			




bool llegar(int jugador, pieza** tablero,int posicion1,int posicion2){
	int cambio=0;
	if(jugador==1){
		cambio=2;
	}else{
		cambio=1;	
	}
	int cuantas_en_jaque=0;	
	int movimiento1=0;
	int movimiento2=0;
	int movimiento3=0;
	int movimiento4=0;	
	int movimiento5=0;
	int movimiento6=0;
	int movimiento7=0;
	int movimiento8=0;	
	int copiadepo1=posicion1;
	int copiadepo2=posicion2;	
	int valida=0;
	valida=1;
	int area_ocupada=2;
	posicion1=posicion1+1;
	int posibles_hackes=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
										
				
		}else{
			if(tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
					movimiento1=1;
					posibles_hackes++;					
					break;
			}else{	
					
					break;
			}				
		}
		posicion1=posicion1+1;	
	}

	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento1==1){
		posicion1=posicion1+1;	
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}							
				
			}else{
				break;			
			}
			posicion1=posicion1+1;	
		}
	}	
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	posicion1=posicion1-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					movimiento2=1;
					posibles_hackes++;
										
					break;
			}else{	
					
					break;
			}				
		}	
		posicion1=posicion1-1;
	}
	
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento2==1){
		
		posicion1=posicion1-1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}						
				
			}else{
				break;			
			}
			posicion1=posicion1-1;
		}		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	posicion2=posicion2+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					movimiento3=1;
					posibles_hackes++;
										
					break;
			}else{	
					
					break;
			}				
		}
		posicion2=posicion2+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento3==1){
		posicion2=posicion2+1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}						
				
			}else{
				break;			
			}
			posicion2=posicion2+1;	
		}				
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	posicion2=posicion2-1;
	
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					movimiento4=1;
					
										
					break;
			}else{	
					
					break;
			}				
		}
		posicion2=posicion2-1;
			  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento4==1){
		posicion2=posicion2-1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}						
				
			}else{
				break;			
			}
			posicion2=posicion2-1;	
		}				
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
//****************************************************************************************
	
	posicion1=posicion1+1;
	posicion2=posicion2+1;
	int cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 					tablero[posicion1][posicion2].getTipo()=='Q')){
				posibles_hackes++;
					
				movimiento5=1;					
				break;
			}else{	
							
				break;
			}							
			
		}
		
		posicion1=posicion1+1;
		posicion2=posicion2+1;		
		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento5==1){
		posicion1=posicion1+1;
		posicion2=posicion2+1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}						
				
			}else{
				break;			
			}
			posicion1=posicion1+1;
			posicion2=posicion2+1;	
		}				
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	
	posicion1=posicion1-1;
	posicion2=posicion2+1;
	
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			
			
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				movimiento6=1;
				posibles_hackes++;
											
				break;
			}else{	
						
				break;
			}				
						
			
		}
		posicion1=posicion1-1;
		posicion2=posicion2+1;		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento6==1){
		posicion1=posicion1-1;
		posicion2=posicion2+1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}							
				
			}else{
				break;			
			}
			posicion1=posicion1-1;
			posicion2=posicion2+1;	
		}				
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	
	posicion1=posicion1-1;
	posicion2=posicion2-1;
	while(posicion1<8 && posicion1>=0 && posicion2-valida>=0 && posicion2-valida<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				movimiento7=1;
				posibles_hackes++;
											
				break;
			}else{	
						
				break;
			}
		}				
		posicion1=posicion1-1;
		posicion2=posicion2-1;		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento7==1){
		posicion1=posicion1-1;
		posicion2=posicion2-1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}							
				
			}else{
				break;			
			}
			posicion1=posicion1-1;
			posicion2=posicion2-1;	
		}				
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	
	posicion1=posicion1+1;
	posicion2=posicion2-1;
	
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				movimiento8=1;	
				posibles_hackes++;
											
				break;
			}else{	
					
				break;
			}				
			
		}
		posicion1=posicion1+1;
		posicion2=posicion2-1;		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	if(movimiento8==1){
		posicion1=posicion1+1;
		posicion2=posicion2-1;
		while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
			
			if(tablero[posicion1][posicion2].getTipo()==' '){
				if(llegar2(cambio,tablero,posicion1,posicion2)==false){
					area_ocupada=0;
				}else{
					area_ocupada=1;					
				}							
				
			}else{
				break;			
			}
			posicion1=posicion1+1;
			posicion2=posicion2-1;	
		}				
	}



	
	
	
	if(area_ocupada==1 ||  area_ocupada==2 ){
		return false;
	}else{
		return true;
	} 
	
}





void salvar(string posiciones){
	ofstream fsalida("juego.txt");
	fsalida<<posiciones;
	fsalida.close();
}
void mover(int pos1,int pos2,int pos3,int pos4,pieza** tablero2){
	tablero2[pos3][pos4].setTipo(tablero2[pos1][pos2].getTipo());				
	tablero2[pos3][pos4].setJugador(tablero2[pos1][pos2].getJugador());
	tablero2[pos1][pos2].setTipo(' ');
	tablero2[pos1][pos2].setJugador(0);

}
				
bool llegar2(int jugador, pieza** tablero,int posicion1,int posicion2){
	
	
	int cuantas_en_jaque=0;	
	
		
	int copiadepo1=posicion1;
	int copiadepo2=posicion2;	
	int valida=0;
	valida=1;
	posicion1=posicion1+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
										
				
		}else{
			if(tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
				
				cuantas_en_jaque++;
										
				break;
			}else{	
					
				break;
			}				
		}
		posicion1=posicion1+1;	
	}


	posicion1=copiadepo1;
	posicion2=copiadepo2;
	posicion1=posicion1-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		
		
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
				cuantas_en_jaque++;
										
				break;
			}else{	
				
				break;
			}				
		}	
		posicion1=posicion1-1;
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2+1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
				cuantas_en_jaque++;
										
				break;
			}else{	
					
				break;
			}				
		}
		posicion2=posicion2+1;	
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion2=posicion2-1;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='T' || tablero[posicion1][posicion2].getTipo()=='Q')){
					
				cuantas_en_jaque++;
										
				break;
			}else{	
					
				break;
			}				
		}
		posicion2=posicion2-1;
			  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;

//****************************************************************************************
	valida=1;
	posicion1=posicion1+1;
	posicion2=posicion2+1;
	int cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 					tablero[posicion1][posicion2].getTipo()=='Q')){
					
				cuantas_en_jaque++;									
				break;
			}else{	
				break;
			}							
			
		}
		
		posicion1=posicion1+1;
		posicion2=posicion2+1;		
		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion1=posicion1-1;
	posicion2=posicion2+1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
							
				
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				cuantas_en_jaque++;											
				break;
			}else{
				break;
			}				
						
			
		}
		posicion1=posicion1-1;
		posicion2=posicion2+1;		
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	posicion1=posicion1-1;
	posicion2=posicion2-1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2-valida>=0 && posicion2-valida<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){			
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				cuantas_en_jaque++;							
				break;
			}else{	
				break;
				}
		}				
		posicion1=posicion1-1;
		posicion2=posicion2-1;		
	}

	posicion1=copiadepo1;
	posicion2=copiadepo2;
	valida=1;
	int h=7;
	posicion1=posicion1+1;
	posicion2=posicion2-1;
	cont1=0;
	while(posicion1<8 && posicion1>=0 && posicion2>=0 && posicion2<8){
		cont1++;
		if(tablero[posicion1][posicion2].getTipo()==' '){
		}else{
			if(  tablero[posicion1][posicion2].getJugador() != jugador &&(tablero[posicion1][posicion2].getTipo()=='A' || 				tablero[posicion1][posicion2].getTipo()=='Q')){
				cuantas_en_jaque++;							
				break;
			}else{	
				break;
			}				
			
		}
		posicion1=posicion1+1;
		posicion2=posicion2-1;		  
	}
	posicion1=copiadepo1;
	posicion2=copiadepo2;
	int pos1=posicion1;
	int pos2=posicion2;


	if(((pos1-2)>=0 && (pos1-2)<8)  && ((pos2+1)>=0 && (pos2+1)<8)){
		if(tablero[pos1-2][pos2+1].getTipo()=='C' && tablero[pos1-2][pos2+1].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}
	}
		
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1-1][pos2+2].getTipo()=='C' && tablero[pos1-1][pos2+2].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}	
	}
	
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2+2)>=0 && (pos2+2)<8)){
		if(tablero[pos1+1][pos2+2].getTipo()=='C' && tablero[pos1+1][pos2+2].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}
	} 
 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2+1)>=0 && (pos2+1)<8)){
		if(tablero[pos1+2][pos2+1].getTipo()=='C' && tablero[pos1+2][pos2+1].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}
	} 
	if(((pos1+2)>=0 && (pos1+2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1+2][pos2-1].getTipo()=='C' && tablero[pos1+2][pos2-1].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}	
	} 
	if(((pos1+1)>=0 && (pos1+1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1+1][pos2-2].getTipo()=='C' && tablero[pos1+1][pos2-2].getJugador() !=jugador){ 		
			cuantas_en_jaque++;
		}
	} 
	if(((pos1-1)>=0 && (pos1-1)<8) && ((pos2-2)>=0 && (pos2-2)<8)){
		if(tablero[pos1-1][pos2-2].getTipo()=='C' && tablero[pos1-1][pos2-2].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}
	}	 
	if(((pos1-2)>=0 && (pos1-2)<8) && ((pos2-1)>=0 && (pos2-1)<8)){
		if(tablero[pos1-2][pos2-1].getTipo()=='C' && tablero[pos1-2][pos2-1].getJugador() !=jugador){ 		
			cuantas_en_jaque++;	
		}	
	}
	if(jugador==1){
		if((pos2>0 && pos2<8) && (pos1-1>0 && pos1-1<8)){
			if(tablero[pos1-1][pos2].getTipo()=='P'){
				cuantas_en_jaque++;			
			}	
		}
		if((pos2>0 && pos2<8) && (pos1-2>0 && pos1-2<8)){
			if(tablero[pos1-1][pos2].getTipo()==' '){
				if(tablero[pos1-2][pos2].getTipo()=='P' && pos1-2==1){
					cuantas_en_jaque++;			
				}
			}	
		}
		
		
	}else{
		if((pos2>0 && pos2<8) && (pos1+1>0 && pos1+1<8)){
			if(tablero[pos1+1][pos2].getTipo()=='P'){
				cuantas_en_jaque++;			
			}	
		}
		if((pos2>0 && pos2<8) && (pos1+2>0 && pos1+2<8)){
			if(tablero[pos1+1][pos2].getTipo()==' '){
				if(tablero[pos1+2][pos2].getTipo()=='P' && pos1+2==1){
					cuantas_en_jaque++;			
				}
			}	
		}
	}
	
	if(cuantas_en_jaque>0 ){
		return true;
	}else{
		return false;
	} 
	
}

