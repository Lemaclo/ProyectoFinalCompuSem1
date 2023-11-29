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

int main(int nargs, char **argsv){
	//Initialize
	initMatrix();
	defaultVariables();

	//Prueba de dibujo:
	tetromino piece = getPiece(T_PIECE);
	drawPiece(&piece);
	printMatrix();
	getchar();

	fall(&piece);
	drawPiece(&piece);
	printMatrix();
	getchar();

	fall(&piece);
	drawPiece(&piece);
	printMatrix();
	getchar();

	fall(&piece);
	drawPiece(&piece);
	printMatrix();
	getchar();

	//Clean up
	clearScreen();
	gotoxy(0,0);
	resetColor();
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
