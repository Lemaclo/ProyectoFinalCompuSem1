/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#ifndef TETRIS_HELPER
#define TETRIS_HELPER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define O_PIECE 0
#define I_PIECE 1
#define T_PIECE 2
#define L_PIECE 3
#define J_PIECE 4
#define S_PIECE 5
#define Z_PIECE 6

//Dimensinoes de la matriz. (10, 20) son las default.
#define MATRIX_X 10
#define MATRIX_Y 20

//Tamaño de los bloques de chars
#define BLOCK_X 2
#define BLOCK_Y 1

//Tamaño de la cola
#define QUEUE_X 4
#define QUEUE_Y 12

//Tamaño del hold
#define HOLD_X 4
#define HOLD_Y 3

//Bloque imprimible
#define BLOCK "█"

//Esto abstrae los colores
typedef struct{
	unsigned char r,g,b;
}pixel;

//Estructura de bloque:
typedef struct{
	short  x,y;
}mino;

//Estructura de movimiento
typedef struct{
	char x,y;
}move;

//Estructura de tetromino:
typedef struct{
	mino body[4];
	move generation_offset[3];
	unsigned char state, id;
	pixel color;
}tetromino;

#include "visuals.h"

void defaultVariables(void);
void generatePiece(tetromino *piece);
tetromino rotateR(tetromino piece);
tetromino rotateL(tetromino piece);
tetromino rotate2(tetromino piece);
tetromino fall(tetromino piece);
tetromino moveR(tetromino piece);
tetromino moveL(tetromino piece);
void erasePiece(tetromino *piece);
unsigned char isEmpty(unsigned char x, unsigned char y);
char legalPiece(tetromino *piece);
char secondCheck(tetromino *piece);
tetromino ghost(tetromino piece);
unsigned char clearLines(void);
void get7Bag(unsigned int pos);
tetromino pop(void);
tetromino holdPiece(tetromino piece);

//Este arreglo guarda la información de la posición inicial de cada pieza.
extern tetromino defaultPositions[7];
extern pixel matrix[MATRIX_Y+2][MATRIX_X];
extern pixel queue[QUEUE_Y][QUEUE_X];
extern pixel hold[HOLD_Y][HOLD_X];
extern tetromino cola[14];

#endif
