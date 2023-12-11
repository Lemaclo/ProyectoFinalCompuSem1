#ifndef VISUALS
#define VISUALS
//En esta versión, quiero implementar TETRIS con gráficos en consola.
#include "screen.h"

//Esta librería tiene funciones para las piezas:
#include "tetris_helper.h"

//Matriz principal del juego
extern pixel matrix[MATRIX_Y+2][MATRIX_X];
//Cola
extern pixel queue[QUEUE_Y][QUEUE_X];
//Hold
extern pixel hold[HOLD_Y][HOLD_X];

extern tetromino cola[14];

void init(int nargs, char **argsv);
void cleanUp(unsigned long score);

void initMatrix(void);
void printMatrix(void);
void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight, unsigned long score);

void initQueue(void);
void updateQueue(void);
void drawInQueue(tetromino piece, int position);
void printQueue(void);

void initHold(void);
tetromino holdPiece(tetromino piece);
void drawInHold(tetromino piece);
void printHold(unsigned int holdRight);

void printScore(unsigned long score);
#endif
