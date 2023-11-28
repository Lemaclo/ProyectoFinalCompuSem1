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

//En esta versión, quiero implementar TETRIS con gráficos en consola.
#include "screen.h"
#define MATRIX_X 10
#define MATRIX_Y 20
#define BLOCK_X 2
#define BLOCK_Y 1
#define BLOCK "█"

typedef struct{
	unsigned char r,g,b;
}pixel;

pixel matrix[MATRIX_Y][MATRIX_Y];

void initMatrix(void);
void printMatrix(void);

int main(int nargs, char **argsv){
	initMatrix();
	printMatrix();
	getchar();
	clearScreen();
	gotoxy(0,0);
	resetColor();
	return 0;
}

//Simplemente inicializamos cada pizel de la matriz en negro.
void initMatrix(void){
	for(int y=0;y<MATRIX_Y;y++){
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
			pixel p = matrix[y][x];
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
