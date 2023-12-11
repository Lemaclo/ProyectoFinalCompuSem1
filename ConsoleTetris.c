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
//Cola
pixel queue[QUEUE_Y][QUEUE_X];
//Hold
pixel hold[HOLD_Y][HOLD_X];

void init(int nargs, char **argsv);
void cleanUp(void);
void initMatrix(void);
void printMatrix(void);
void drawPiece(tetromino *piece);
void drawGhostPiece(tetromino *piece);
void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight);
tetromino getPiece(int id);
void delay(unsigned int milis);
void clearLines(void);
void get7Bag(unsigned int pos);
tetromino pop(void);
tetromino manageInput(int input, tetromino *currentPiece, 
		int *count, tetromino *shadow, int *holdRight);
tetromino ghost(tetromino piece);

void initQueue(void);
void updateQueue(void);
void drawInQueue(tetromino piece, int position);
void printQueue(void);

void initHold(void);
tetromino holdPiece(tetromino piece);
void drawInHold(tetromino piece);
void printHold(unsigned int holdRight);

tetromino cola[14];

int main(int nargs, char **argsv){
	init(nargs, argsv);
	int input, count, timer, set, holdRight;
	tetromino piece, possible, shadow;
	count = set = holdRight = 1;
	timer = 10;
	while((input = getchar()) != 3){
		if (set){	
			clearLines();
			piece = pop();
			updateQueue();
			possible = fall(&piece);
			if(secondCheck(&possible)){
				piece = possible;
			} else {
				//Game over
				break;
			}
			draw(&piece, &shadow, holdRight);
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
		draw(&piece, &shadow, holdRight);
		count++;
	}
	cleanUp();
	return 0;
}

void init(int nargs, char **argsv){
	srand(time(0));
	setRaw();
	setSpecialInput();
	initMatrix();
	initQueue();
	defaultVariables();
	get7Bag(0);
	get7Bag(7);
}

void cleanUp(void){
	//Clean up
	system("clear");
	setCooked();
	gotoxy(0,0);
	resetColor();
	setNormalInput();
	printf("Game over!\n");

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

void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight){
		*shadow = ghost(*piece);
		drawGhostPiece(shadow);
		drawPiece(piece);
		printMatrix();
		printQueue();
		printHold(holdRight);
}

tetromino ghost(tetromino piece){
	erasePiece(&piece);
	tetromino possible = piece;
	while (secondCheck(&possible) && firstCheck(&possible)){
			possible = fall(&possible);
	}
	possible.body[0].y--;
	generatePiece(&possible);
	drawPiece(&piece);
	return possible;
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

void drawGhostPiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x].r = piece->color.r / 3;
		matrix[piece->body[i].y][piece->body[i].x].g = piece->color.g / 3;
		matrix[piece->body[i].y][piece->body[i].x].b = piece->color.b / 3;
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

void initQueue(void){
	for(int y=0;y<QUEUE_Y;y++){
		for(int x=0;x<QUEUE_X;x++){
			queue[y][x].r = 0;
			queue[y][x].g = 0;
			queue[y][x].b = 0;
		}
	}

}

void drawInQueue(tetromino piece, int position){
	piece.body[0].x = 1;
	piece.body[0].y = position * 3 + 1;
	generatePiece(&piece);
	for (int i=0;i<4;i++){
		queue[piece.body[i].y][piece.body[i].x] = piece.color;
	}
}

void updateQueue(void){
	initQueue();
	for (int i=0;i<4;i++){
		drawInQueue(cola[i], i);
	}
}

void printQueue(void){
	//Hacemos el reescalamiento de coordenadas
	int origin_x = 11 * BLOCK_X + (SIZE_X-MATRIX_X*BLOCK_X)/2;
	int origin_y = BLOCK_Y + (SIZE_Y-MATRIX_Y*BLOCK_Y)/2;
	//Iteramos sobre cada pixel de la matriz
	for(int y=0;y<QUEUE_Y;y++){
		for(int x=0;x<QUEUE_X;x++){
			pixel p = queue[y][x];
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
	gotoxy(origin_x + BLOCK_X, origin_y - BLOCK_Y);
	setColor(255, 255, 255);
	printf("Next");
}

void initHold(void){
	for(int y=0;y<HOLD_Y;y++){
		for(int x=0;x<HOLD_X;x++){
			hold[y][x].r = 0;
			hold[y][x].g = 0;
			hold[y][x].b = 0;
		}
	}

}

tetromino holdPiece(tetromino piece){
	static tetromino currentHold;
	static unsigned int count;
	tetromino response;
	if (count == 0){
		currentHold = defaultPositions[piece.id];
		response = pop();
		response = fall(&response);
		updateQueue();
		drawInHold(currentHold);
		count++;
		return response;
	}
	response = fall(&currentHold);
	currentHold = defaultPositions[piece.id];
	drawInHold(currentHold);
	return response;
}

void drawInHold(tetromino piece){
	initHold();
	piece.body[0].x = 1;
	piece.body[0].y = 1;
	generatePiece(&piece);
	for(int i=0;i<4;i++){
		hold[piece.body[i].y][piece.body[i].x] = piece.color;
	}
}

void printHold(unsigned int holdRight){
	//Hacemos el reescalamiento de coordenadas
	int origin_x = (SIZE_X-MATRIX_X*BLOCK_X)/2 - (5 * BLOCK_X);
	int origin_y = BLOCK_Y + (SIZE_Y-MATRIX_Y*BLOCK_Y)/2;
	//Iteramos sobre cada pixel de la matriz
	for(int y=0;y<HOLD_Y;y++){
		for(int x=0;x<HOLD_X;x++){
			pixel p = hold[y][x];
			if ((p.r | p.g | p.b) >= 0x80 && !holdRight){
				setColor(0xC0, 0xC0, 0xC0);
			} else {
				setColor(p.r,p.g,p.b);
			}
			//Utilizamos el color del pixel actual
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
	gotoxy(origin_x + BLOCK_X, origin_y - BLOCK_Y);
	setColor(255, 255, 255);
	printf("Hold");
}
