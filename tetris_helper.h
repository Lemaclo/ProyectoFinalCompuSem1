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

//Esto abstrae los colores
typedef struct{
	unsigned char r,g,b;
}pixel;

//Estructura de bloque:
typedef struct{
	unsigned char x,y;
}mino;

//Estructura de movimiento
typedef struct{
	char x,y;
}move;

//Estructura de tetromino:
typedef struct{
	mino body[4];
	move generation_offset[3];
	unsigned char state;
	pixel color;
}tetromino;

void defaultVariables(void);
void generatePiece(tetromino *piece);
void rotateR(tetromino *piece);
void rotateL(tetromino *piece);
void rotate2(tetromino *piece);
void fall(tetromino *piece);
void moveR(tetromino *piece);
void moveL(tetromino *piece);

//Este arreglo guarda la información de la posición inicial de cada pieza.
extern tetromino defaultPositions[7];

#endif
