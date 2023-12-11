/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include "visuals.h"

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

void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight, unsigned long score){
		*shadow = ghost(*piece);
		drawGhostPiece(shadow);
		drawPiece(piece);
		printMatrix();
		printQueue();
		printHold(holdRight);
		printScore(score);
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

void printScore(unsigned long score){
	int origin_x = (SIZE_X-MATRIX_X*BLOCK_X)/2 - 5*BLOCK_X;
	int origin_y = (SIZE_Y+MATRIX_Y*BLOCK_Y)/2 - 4*BLOCK_Y;
	setColor(255,255,255);
	gotoxy(origin_x, origin_y);
	printf("Score:");
	gotoxy(origin_x, origin_y + 1);
	printf("%lu", score);
}
