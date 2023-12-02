/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//En esta versión, quiero implementar TETRIS con gráficos en consola.
#include "screen.h"

//Esta librería tiene funciones para las piezas:
#include "tetris_helper.h"


//Piezas por default
tetromino defaultPositions[7];

//Matriz principal del juego
pixel matrix[MATRIX_Y+2][MATRIX_X];

void initMatrix(void);
void printMatrix(void);
void drawPiece(tetromino *piece);
tetromino getPiece(int id);
void delay(unsigned int milis);
int getInput(void);
void clearLines(void);
void get7Bag(unsigned int pos);
tetromino pop(void);

tetromino cola[14];

int main(int nargs, char **argsv){
	srand(time(0));
	setRaw();
	setSpecialInput();
	//Initialize
	initMatrix();
	defaultVariables();
	get7Bag(0);
	get7Bag(7);

	//Prueba de dibujo:
	tetromino piece = pop();
	piece = fall(&piece);
	drawPiece(&piece);
	printMatrix();
	int input;
	int count = 0;
	int timer = nargs == 2 ? atoi(argsv[1]) : 10;
	int set = 0;
	while((input = getchar()) != 3){
		if (set){	
			//printf("\a");
			clearLines();
			piece = pop();
			drawPiece(&piece);
			printMatrix();
			set = 0;
		}
		count++;
		tetromino possible;
		switch(input){
			case -1:
				possible = piece;
				rewind(stdin);
				break;
			case 'a':
				possible = moveL(&piece);
				break;
			case 'd':
				possible = moveR(&piece);
				break;
			case 's':
				count = timer;
				break;
			case 'w':
				int final = 1;
				possible = piece;
				count = timer;
				do{
					possible = fall(&piece);
					if(firstCheck(&possible)){
						erasePiece(&piece);
						if (secondCheck(&possible)){
							piece = possible;
						} else {
							final = 0;
						}
					} else {
						final = 0;
					}
				} while(final);
				break;
			case 27://Esto es para las flechas.
				if(getchar() == 91){
					switch(getchar()){
						case 68:
							//printf("\a");
							possible = rotateL(&piece);
							break;
						case 67:
							//printf("\a");
							possible = rotateR(&piece);
							break;
						case 66:
							//printf("\a");
							possible = rotate2(&piece);
							break;
						default:
							possible = piece;
							break;
					}
				}
				break;
			default:
				possible = piece;
				rewind(stdin);
				break;
		}

		//Verifica si es valido el movimiento actual
		if(firstCheck(&possible)){
			erasePiece(&piece);
			if (secondCheck(&possible)){
				piece = possible;
			}
		}

		//Intenta caer
		if(count % timer == 0){
			possible = fall(&piece);
			if(firstCheck(&possible)){
				erasePiece(&piece);
				if (secondCheck(&possible)){
					piece = possible;
				} else {
					set = 1;
				}
			} else {
				set = 1;
			}
		}
		drawPiece(&piece);
		printMatrix();
		//fflush(stdout);
		//delay(200);
	}

	//Clean up
	clearScreen();
	setCooked();
	gotoxy(0,0);
	resetColor();
	setNormalInput();
	return 0;
}

//Simplemente inicializamos cada pizel de la matriz en negro.
void initMatrix(void){
	for(int y=2;y<MATRIX_Y;y++){
		for(int x=0;x<MATRIX_X;x++){
			matrix[y][x].r = 0;
			matrix[y][x].g = 0;
			matrix[y][x].b = 0;
		}
	}
}

void printMatrix(void){
	//Primero, limpiamos la pantalla
	clearScreen();
	//Hacemos el reescalamiento de coordenadas
	int origin_x = (SIZE_X-MATRIX_X*BLOCK_X)/2;
	int origin_y = (SIZE_Y-MATRIX_Y*BLOCK_Y)/2;
	//Iteramos sobre cada pixel de la matriz
	for(int y=0;y<MATRIX_Y;y++){
		for(int x=0;x<MATRIX_X;x++){
			pixel p = matrix[y+2][x];
			//Utilizamos el color del pixel actual
			setColor(p.r,p.g,p.b);
			//Esto es para imprimir los bloques
			//que representan un pixel.
			for(int i=0;i<BLOCK_Y;i++){
				gotoxy(origin_x + x*BLOCK_X, origin_y + y*BLOCK_Y + i);
				for(int j=0;j<BLOCK_X;j++){
					printf(BLOCK);
				}
			}
		}
	}
}

//Agrega una pieza a la matriz que se dibuja.
void drawPiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x] = piece->color;
	}
}

//Esto únicamente es una función para que haga una copia y no toque el original.
tetromino getPiece(int id){
	return defaultPositions[id];
}

//Esta función pausa el programa durante milis milisegundos.
void delay(unsigned int milis){
	clock_t finish = clock() + (milis * CLOCKS_PER_SEC) / 1000;
	while (finish - clock() > 0){
		;
	}
}

int getInput(void){
	int c = getchar();
	return c;
}

//Esto hace desaparecer las lineas que ya se completaron de la matriz.
void clearLines(void){
	for(int i=2;i<MATRIX_Y+2;i++){
		int flag = 0;
		for(int j=0;j<MATRIX_X;j++){
			if(isEmpty(j,i) == 0){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		printf("\a");
		for(int k=i;k>2;k--){
			for(int l=0;l<MATRIX_X;l++){
				matrix[k][l] = matrix[k-1][l];
			}
		}
		for(int k=2;k<MATRIX_X;k++){
			matrix[0][k].r = 0;
			matrix[0][k].g = 0;
			matrix[0][k].b = 0;
		}
	}

}

//Copia 7 tetrominos directamente a la cola. Pos unicamente 
//puede ser 0 o 7.
void get7Bag(unsigned int pos){
	tetromino shuffled[7];
	memcpy(shuffled, defaultPositions, sizeof(tetromino) * 7);
	for (int i=0;i<7;i++){
		int j = rand() % (i+1);
		if (i != j){
			tetromino temp = shuffled[i];
			shuffled[i] = shuffled[j];
			shuffled[j] = temp;
		}
	}
	memcpy(cola + pos, shuffled, 7 * sizeof(tetromino));
}

tetromino pop(void){
	static int count;
	tetromino ready = cola[0];
	memcpy(cola, cola + 1, 13 * sizeof(tetromino));
	count ++;
	if (count % 7 == 0) get7Bag(7);
	return ready;
}
