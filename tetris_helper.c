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

	defaultPositions[0].color.r = 0xff;
	defaultPositions[0].color.g = 0xff;
	defaultPositions[0].color.b = 0x0;

	//Pieza I

	defaultPositions[1].generation_offset[0].x = -1;
	defaultPositions[1].generation_offset[0].y = 0;

	defaultPositions[1].generation_offset[1].x = 2;
	defaultPositions[1].generation_offset[1].y = 0;

	defaultPositions[1].generation_offset[2].x = 1;
	defaultPositions[1].generation_offset[2].y = 0;

	defaultPositions[1].color.r = 0x0;
	defaultPositions[1].color.g = 0xff;
	defaultPositions[1].color.b = 0xff;

	//Pieza T

	defaultPositions[2].generation_offset[0].x = -1;
	defaultPositions[2].generation_offset[0].y = 0;

	defaultPositions[2].generation_offset[1].x = 0;
	defaultPositions[2].generation_offset[1].y = 1;

	defaultPositions[2].generation_offset[2].x = 1;
	defaultPositions[2].generation_offset[2].y = 0;

	defaultPositions[2].color.r = 0x80;
	defaultPositions[2].color.g = 0x0;
	defaultPositions[2].color.b = 0x80;
	
	//Pieza L

	defaultPositions[3].generation_offset[0].x = -1;
	defaultPositions[3].generation_offset[0].y = 0;

	defaultPositions[3].generation_offset[1].x = 1;
	defaultPositions[3].generation_offset[1].y = 1;

	defaultPositions[3].generation_offset[2].x = 1;
	defaultPositions[3].generation_offset[2].y = 0;

	defaultPositions[3].color.r = 0xff;
	defaultPositions[3].color.g = 0x7f;
	defaultPositions[3].color.b = 0x00;

	//Pieza J

	defaultPositions[4].generation_offset[0].x = -1;
	defaultPositions[4].generation_offset[0].y = 0;

	defaultPositions[4].generation_offset[1].x = -1;
	defaultPositions[4].generation_offset[1].y = 1;

	defaultPositions[4].generation_offset[2].x = 1;
	defaultPositions[4].generation_offset[2].y = 0;

	defaultPositions[4].color.r = 0x00;
	defaultPositions[4].color.g = 0x00;
	defaultPositions[4].color.b = 0xff;

	//Pieza S

	defaultPositions[5].generation_offset[0].x = -1;
	defaultPositions[5].generation_offset[0].y = 0;

	defaultPositions[5].generation_offset[1].x = 0;
	defaultPositions[5].generation_offset[1].y = 1;

	defaultPositions[5].generation_offset[2].x = 1;
	defaultPositions[5].generation_offset[2].y = 1;

	defaultPositions[5].color.r = 0x00;
	defaultPositions[5].color.g = 0xff;
	defaultPositions[5].color.b = 0x00;

	//Pieza Z

	defaultPositions[6].generation_offset[0].x = -1;
	defaultPositions[6].generation_offset[0].y = 1;

	defaultPositions[6].generation_offset[1].x = 0;
	defaultPositions[6].generation_offset[1].y = 1;

	defaultPositions[6].generation_offset[2].x = 1;
	defaultPositions[6].generation_offset[2].y = 0;

	defaultPositions[6].color.r = 0xff;
	defaultPositions[6].color.g = 0x00;
	defaultPositions[6].color.b = 0x00;

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
		piece->body[i].y = piece->body[0].y - piece->generation_offset[i-1].y;
	}
}

void rotateR(tetromino *piece){
	erasePiece(piece);
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		piece->generation_offset[i].x = piece->generation_offset[i].y;
		piece->generation_offset[i].y = -1*temp;
	}
	generatePiece(piece);
}

void rotateL(tetromino *piece){
	erasePiece(piece);
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		piece->generation_offset[i].x = -1 * piece->generation_offset[i].y;
		piece->generation_offset[i].y = temp;
	}
	generatePiece(piece);
}

void rotate2(tetromino *piece){
	erasePiece(piece);
	for(int i=0;i<3;i++){
		piece->generation_offset[i].x *= -1;
		piece->generation_offset[i].y *= -1;
	}
	generatePiece(piece);
}

void fall(tetromino *piece){
	erasePiece(piece);
	piece->body[0].y++;
	generatePiece(piece);
}

void moveR(tetromino *piece){
	erasePiece(piece);
	piece->body[0].x++;
	generatePiece(piece);
}

void moveL(tetromino *piece){
	erasePiece(piece);
	piece->body[0].x--;
	generatePiece(piece);
}

void erasePiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x].r = 0;
		matrix[piece->body[i].y][piece->body[i].x].g = 0;
		matrix[piece->body[i].y][piece->body[i].x].b = 0;
	}
}

unsigned char isEmpty(unsigned char x, unsigned char y){
	return matrix[y][x].r | matrix[y][x].g | matrix[y][x].b;
}

char validatePiecePosition(tetromino *piece){
	for(int i=0;i<4;i++){
		short x = piece->body[i].x;
		short y = piece->body[i].y;
		if(x < 0 || x >= MATRIX_X) return 0;
		if(y < 0 || y >= MATRIX_Y) return 0;
		if(!isEmpty(x,y)) return 0;
	}
	return 1;
}
