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

	defaultPositions[0].id = O_PIECE;

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

	defaultPositions[1].id = I_PIECE;

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
	
	defaultPositions[2].id = T_PIECE;

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

	defaultPositions[3].id = L_PIECE;

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

	defaultPositions[4].id = J_PIECE;

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

	defaultPositions[5].id = S_PIECE;

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

	defaultPositions[6].id = Z_PIECE;

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

tetromino rotateR(tetromino *piece){
	tetromino babyPiece = *piece;
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		babyPiece.generation_offset[i].x = piece->generation_offset[i].y;
		babyPiece.generation_offset[i].y = -1*temp;
	}
	generatePiece(&babyPiece);
	return babyPiece;
}

tetromino rotateL(tetromino *piece){
	tetromino babyPiece = *piece;
	for(int i=0;i<3;i++){
		char temp = piece->generation_offset[i].x; 
		babyPiece.generation_offset[i].x = -1 * piece->generation_offset[i].y;
		babyPiece.generation_offset[i].y = temp;
	}
	generatePiece(&babyPiece);
	return babyPiece;
}

tetromino rotate2(tetromino *piece){
	tetromino babyPiece = *piece;
	for(int i=0;i<3;i++){
		babyPiece.generation_offset[i].x *= -1;
		babyPiece.generation_offset[i].y *= -1;
	}
	generatePiece(&babyPiece);
	return babyPiece;
}

tetromino fall(tetromino *piece){
	tetromino babyPiece = *piece;
	babyPiece.body[0].y++;
	generatePiece(&babyPiece);
	return babyPiece;
}

tetromino moveR(tetromino *piece){
	tetromino babyPiece = *piece;
	babyPiece.body[0].x++;
	generatePiece(&babyPiece);
	return babyPiece;
}

tetromino moveL(tetromino *piece){
	tetromino babyPiece = *piece;
	babyPiece.body[0].x--;
	generatePiece(&babyPiece);
	return babyPiece;
}

void erasePiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x].r = 0;
		matrix[piece->body[i].y][piece->body[i].x].g = 0;
		matrix[piece->body[i].y][piece->body[i].x].b = 0;
	}
}

unsigned char isEmpty(unsigned char x, unsigned char y){
	return (matrix[y][x].r | matrix[y][x].g | matrix[y][x].b) >= 0x80;
}

char legalPiece(tetromino *piece){
	for(int i=0;i<4;i++){
		short x = piece->body[i].x;
		short y = piece->body[i].y;
		if(x < 0 || x >= MATRIX_X) return 0;
		if(y < 0 || y >= MATRIX_Y + 2) return 0;
		if(isEmpty(x,y) != 0) return 0;
	}
	return 1;
}

char firstCheck(tetromino *piece){
	for(int i=0;i<4;i++){
		short x = piece->body[i].x;
		short y = piece->body[i].y;
		if(x < 0 || x >= MATRIX_X) return 0;
		if(y < 0 || y >= MATRIX_Y + 2) return 0;
	}
	return 1;
}

char secondCheck(tetromino *piece){
	for(int i=0;i<4;i++){
		short x = piece->body[i].x;
		short y = piece->body[i].y;
		if(isEmpty(x,y) != 0) return 0;
	}
	return 1;
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

//Esto hace desaparecer las lineas que ya se completaron de la matriz.
unsigned char clearLines(void){
	unsigned char linesCleared = 0;
	for(int i=2;i<MATRIX_Y+2;i++){
		int flag = 0;
		for(int j=0;j<MATRIX_X;j++){
			if(isEmpty(j,i) == 0){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		linesCleared++;
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
		if (linesCleared >= 4) break;
	}
	return linesCleared;
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
