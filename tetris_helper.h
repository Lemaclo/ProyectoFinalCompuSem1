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
	unsigned char state;
	pixel color;
}tetromino;

void defaultVariables(void);
void generatePiece(tetromino *piece);
tetromino rotateR(tetromino *piece);
tetromino rotateL(tetromino *piece);
tetromino rotate2(tetromino *piece);
tetromino fall(tetromino *piece);
tetromino moveR(tetromino *piece);
tetromino moveL(tetromino *piece);
void erasePiece(tetromino *piece);
unsigned char isEmpty(unsigned char x, unsigned char y);
char firstCheck(tetromino *piece);
char secondCheck(tetromino *piece);
char legalPiece(tetromino *piece);

//Este arreglo guarda la información de la posición inicial de cada pieza.
extern tetromino defaultPositions[7];
extern pixel matrix[MATRIX_Y+2][MATRIX_X];

#endif
