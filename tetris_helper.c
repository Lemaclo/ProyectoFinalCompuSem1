/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include "tetris_helper.h"

void defaultVariables(void){
	//Pieza O

	defaultPositions[0].generation_offset[0].x = 0;
	defaultPositions[0].generation_offset[0].y = 1;

	defaultPositions[0].generation_offset[1].x = 1;
	defaultPositions[0].generation_offset[1].y = 1;

	defaultPositions[0].generation_offset[2].x = 1;
	defaultPositions[0].generation_offset[2].y = 0;

	//Pieza I

	defaultPositions[1].generation_offset[0].x = -1;
	defaultPositions[1].generation_offset[0].y = 0;

	defaultPositions[1].generation_offset[1].x = 2;
	defaultPositions[1].generation_offset[1].y = 0;

	defaultPositions[1].generation_offset[2].x = 1;
	defaultPositions[1].generation_offset[2].y = 0;

	//Pieza T

	defaultPositions[2].generation_offset[0].x = -1;
	defaultPositions[2].generation_offset[0].y = 0;

	defaultPositions[2].generation_offset[1].x = 0;
	defaultPositions[2].generation_offset[1].y = 1;

	defaultPositions[2].generation_offset[2].x = 1;
	defaultPositions[2].generation_offset[2].y = 0;

	//Pieza L

	defaultPositions[3].generation_offset[0].x = -1;
	defaultPositions[3].generation_offset[0].y = 0;

	defaultPositions[3].generation_offset[1].x = 1;
	defaultPositions[3].generation_offset[1].y = 1;

	defaultPositions[3].generation_offset[2].x = 1;
	defaultPositions[3].generation_offset[2].y = 0;

	//Pieza J

	defaultPositions[4].generation_offset[0].x = -1;
	defaultPositions[4].generation_offset[0].y = 0;

	defaultPositions[4].generation_offset[1].x = -1;
	defaultPositions[4].generation_offset[1].y = 1;

	defaultPositions[4].generation_offset[2].x = 1;
	defaultPositions[4].generation_offset[2].y = 0;

	//Pieza S

	defaultPositions[5].generation_offset[0].x = -1;
	defaultPositions[5].generation_offset[0].y = 0;

	defaultPositions[5].generation_offset[1].x = 0;
	defaultPositions[5].generation_offset[1].y = 1;

	defaultPositions[5].generation_offset[2].x = 1;
	defaultPositions[5].generation_offset[2].y = 1;

	//Pieza Z

	defaultPositions[6].generation_offset[0].x = -1;
	defaultPositions[6].generation_offset[0].y = 1;

	defaultPositions[6].generation_offset[1].x = 0;
	defaultPositions[6].generation_offset[1].y = 1;

	defaultPositions[6].generation_offset[2].x = 1;
	defaultPositions[6].generation_offset[2].y = 0;

	//Cada pieza empieza con estado 0 (sin rotar):

	for(int i=0;i<7;i++){
		defaultPositions[i].body[0].x = 4;
		defaultPositions[i].body[0].y = 1;
		defaultPositions[i].state = 0;
		generatePiece(&defaultPositions[i]);
	}

}

void generatePiece(tetromino *piece){
	for(int i=1;i<4;i++){
		piece->body[i].x = piece->body[0].x + piece->generation_offset[i-1].x;
		piece->body[i].y = piece->body[0].y + piece->generation_offset[i-1].y;
	}
}

void rotateR(tetromino *piece){
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		piece->generation_offset[i].x = piece->generation_offset[i].y;
		piece->generation_offset[i].y = -1*temp;
	}
	generatePiece(piece);
}

void rotateL(tetromino *piece){
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		piece->generation_offset[i].x = -1 * piece->generation_offset[i].y;
		piece->generation_offset[i].y = temp;
	}
	generatePiece(piece);
}

void rotate2(tetromino *piece){
	for(int i=0;i<3;i++){
		piece->generation_offset[i].x *= -1;
		piece->generation_offset[i].y *= -1;
	}
	generatePiece(piece);
}

void fall(tetromino *piece){
	piece->body[0].y++;
	generatePiece(piece);
}

void moveR(tetromino *piece){
	piece->body[0].x++;
	generatePiece(piece);
}

void moveL(tetromino *piece){
	piece->body[0].x--;
	generatePiece(piece);
}