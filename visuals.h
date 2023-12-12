/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

/* En esta librería hay funciones para trabajar con las tres
 * zonas de dibujo: la matriz del juego, la cola, y el hold.
 * Las funciones son para inicializar, actualizar, y
 * mostrar esas zonas de juego. Cada una de ellas se representa
 * como una matriz de pixeles.
 */

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

//Funciones generales
void init(int nargs, char **argsv);
void cleanUp(unsigned long score);

//Funciones de la matriz del juego
void initMatrix(void);
void printMatrix(void);
void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight, unsigned long score);
void erasePiece(tetromino *piece);
void drawPiece(tetromino *piece);
void drawGhostPiece(tetromino *piece);

//Funciones de la cola
void initQueue(void);
void updateQueue(void);
void drawInQueue(tetromino piece, int position);
void printQueue(void);

//Funciones del hold
void initHold(void);
void drawInHold(tetromino piece);
void printHold(unsigned int holdRight);

//Función del puntaje
void printScore(unsigned long score);

#endif
