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
#include <math.h>

//En esta versión, quiero implementar TETRIS con gráficos en consola.
#include "screen.h"

//Esta librería tiene funciones para las piezas:
#include "tetris_helper.h"
#include "visuals.h"


//Piezas por default
tetromino defaultPositions[7];

//Matriz principal del juego
pixel matrix[MATRIX_Y+2][MATRIX_X];
//Cola
pixel queue[QUEUE_Y][QUEUE_X];
//Hold
pixel hold[HOLD_Y][HOLD_X];

tetromino manageInput(int input, tetromino *currentPiece, 
		int *count, tetromino *shadow, int *holdRight);

void updateScore(unsigned long *score, unsigned char linesCleared, int timer);

tetromino cola[14];

int main(int nargs, char **argsv){
	init(nargs, argsv);
	int input, count, timer, set, holdRight;
	unsigned long score = 0;
	tetromino piece, possible, shadow;
	count = set = holdRight = 1;
	timer = 10;
	while((input = getchar()) != 3){
		if (set){	
			unsigned char lines = clearLines();
			updateScore(&score, lines, timer);
			timer = 10 - (int)log2f(score/1000);
			piece = pop();
			updateQueue();
			possible = fall(&piece);
			if(secondCheck(&possible)){
				piece = possible;
			} else {
				//Game over
				break;
			}
			draw(&piece, &shadow, holdRight, score);
			set = 0;
			holdRight = 1;
			//delay(200);
		}
		possible = manageInput(input, &piece, &count, &shadow, &holdRight);
		//Verifica si es valido el movimiento actual
		erasePiece(&piece);
		if(legalPiece(&possible)){
			piece = possible;
		}
		//Intenta caer
		if(count % timer == 0){
			possible = fall(&piece);
			erasePiece(&piece);
			if(legalPiece(&possible)){
				piece = possible;
			} else {
				set = 1;
			}
		}
		erasePiece(&shadow);
		draw(&piece, &shadow, holdRight, score);
		count++;
	}
	cleanUp();
	return 0;
}


tetromino manageInput(int input, tetromino *piece, int *count, tetromino *shadow, int *holdRight){
	switch(input){
		case 'a':
			return moveL(piece);
		case 'd':
			return moveR(piece);
		case 's':
			*count = 0;
			return *piece;
		case 'w':
			*count = 0;
			return *shadow;
		//Esto es para las flechas.
		case 27:
			if(getchar() == 91){
				switch(getchar()){
					case 68:
						return rotateL(piece);
					case 67:
						return rotateR(piece);
					case 66:
						return rotate2(piece);
					case 65:
						if (*holdRight){
							*holdRight = 0;
							return holdPiece(*piece);
						}
					default:
						break;
				}
			}
		case -1:
			rewind(stdin);
			return *piece;
		default:
			return *piece;
	}
}

void updateScore(unsigned long *score, unsigned char linesCleared, int timer){
	static unsigned char combo;
	unsigned int points = 0;
	switch (linesCleared){
		case 0:
			combo = 1;
			return;
		case 1:
			points += 100;
			break;
		case 2:
			points += 300;
			break;
		case 3:
			points += 500;
			break;
		case 4:
			points += 1000;
			break;
		default:
			points -= 100000;
			break;
	}
	points *= (11 - timer);
	points *= combo;
	combo++;
	*score += points;
}
