/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include "visuals.h"

//Realiza varios preparativos necesarios para correr el juego.
//Pone la terminal en modo crudo y con límite de tiempo
//para los inputs, inicializa todas las zonas de dibujo en 
//negro, prepara los valores por default de las piezas, 
//y crea las primeras dos bolsas de tetrominos.
void init(int nargs, char **argsv){
	srand(time(0));
	setRaw();
	setSpecialInput();
	initMatrix();
	initQueue();
	initHold();
	defaultVariables();
	get7Bag(0);
	get7Bag(7);
}

//Limpia la pantalla, reinicia los modos de la terminal, 
//e imprime el resultado final. Después de está función, 
//la música sigue sonando hasta que se presione Ctrl + C.
void cleanUp(unsigned long score){
	system("clear");
	setCooked();
	gotoxy(0,0);
	resetColor();
	setNormalInput();
	printf("Game over!\n");
	printf("Tu puntaje final fue: %lu.\n", score);
	printf("Presiona Ctrl+C para salir.\n");

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

//Esta función imprime todas las zonas de dibujo: la matriz, 
//la cola, y el hold. También crea la sombra de la pieza actual.
void draw(tetromino *piece, tetromino *shadow, unsigned int holdRight, unsigned long score){
		*shadow = ghost(*piece);
		drawGhostPiece(shadow);
		drawPiece(piece);
		printMatrix();
		printQueue();
		printHold(holdRight);
		printScore(score);
}

//Imprime la matriz del juego.
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

//Inicializamos cada pixel del la cola en negro.
void initQueue(void){
	for(int y=0;y<QUEUE_Y;y++){
		for(int x=0;x<QUEUE_X;x++){
			queue[y][x].r = 0;
			queue[y][x].g = 0;
			queue[y][x].b = 0;
		}
	}

}

//Guarda una pieza en la matrix que representa el display
//de la cola, para que se vea la próxima vez que se llame 
//printQueue. 
//El argumento position puede ser únicamente 0,1,2 o 3.
void drawInQueue(tetromino piece, int position){
	piece.body[0].x = 1;
	piece.body[0].y = position * 3 + 1;
	generatePiece(&piece);
	for (int i=0;i<4;i++){
		queue[piece.body[i].y][piece.body[i].x] = piece.color;
	}
}

//Borra el display de la cola (no afecta a la 
//cola real de tetrominos) y lo actualiza según la cola real.
void updateQueue(void){
	initQueue();
	for (int i=0;i<4;i++){
		drawInQueue(cola[i], i);
	}
}

//Imprime la cola. La función es análoga a printMatrix().
void printQueue(void){
	int origin_x = 11 * BLOCK_X + (SIZE_X-MATRIX_X*BLOCK_X)/2;
	int origin_y = BLOCK_Y + (SIZE_Y-MATRIX_Y*BLOCK_Y)/2;
	for(int y=0;y<QUEUE_Y;y++){
		for(int x=0;x<QUEUE_X;x++){
			pixel p = queue[y][x];
			setColor(p.r,p.g,p.b);
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

//Inicializa todos los pixeles del hold a negro.
void initHold(void){
	for(int y=0;y<HOLD_Y;y++){
		for(int x=0;x<HOLD_X;x++){
			hold[y][x].r = 0;
			hold[y][x].g = 0;
			hold[y][x].b = 0;
		}
	}

}

//Guarda una pieza en la matrix que representa el display
//del hold, para que se vea cuando se llame printHold.
//El hold únicamente puede mostrar una pieza a la vez, 
//así que la nueva pieza reemplaza a la anterior.
void drawInHold(tetromino piece){
	initHold();
	piece.body[0].x = 1;
	piece.body[0].y = 1;
	generatePiece(&piece);
	for(int i=0;i<4;i++){
		hold[piece.body[i].y][piece.body[i].x] = piece.color;
	}
}

//Imprime el hold. La función es análoga a printMatrix().
void printHold(unsigned int holdRight){
	int origin_x = (SIZE_X-MATRIX_X*BLOCK_X)/2 - (5 * BLOCK_X);
	int origin_y = BLOCK_Y + (SIZE_Y-MATRIX_Y*BLOCK_Y)/2;
	for(int y=0;y<HOLD_Y;y++){
		for(int x=0;x<HOLD_X;x++){
			pixel p = hold[y][x];
			if ((p.r | p.g | p.b) >= 0x80 && !holdRight){
				setColor(0xC0, 0xC0, 0xC0);
			} else {
				setColor(p.r,p.g,p.b);
			}
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

//Imprime el puntaje actual. El puntaje no usa una matriz de 
//pixeles, pues únicamente imprime texto.
void printScore(unsigned long score){
	int origin_x = (SIZE_X-MATRIX_X*BLOCK_X)/2 - 5*BLOCK_X;
	int origin_y = (SIZE_Y+MATRIX_Y*BLOCK_Y)/2 - 4*BLOCK_Y;
	setColor(255,255,255);
	gotoxy(origin_x, origin_y);
	printf("Score:");
	gotoxy(origin_x, origin_y + 1);
	printf("%lu", score);
}

//Establece el color en negro de todos los
//pixeles que componen una pieza particular.
void erasePiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x].r = 0;
		matrix[piece->body[i].y][piece->body[i].x].g = 0;
		matrix[piece->body[i].y][piece->body[i].x].b = 0;
	}
}

//Agrega una pieza a la matriz del juego. Toma la posición
//guardada en la propia pieza para hacerlo. De esta manera, la
//pieza se verá en pantalla al llamar printMatrix().
void drawPiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x] = piece->color;
	}
}

//Hace casi lo mismo que drawPiece, pero dibuja unos tonos más apagados, 
//para simular transparencia de la sombra de los tetrominos.
void drawGhostPiece(tetromino *piece){
	for(int i=0;i<4;i++){
		matrix[piece->body[i].y][piece->body[i].x].r = piece->color.r / 3;
		matrix[piece->body[i].y][piece->body[i].x].g = piece->color.g / 3;
		matrix[piece->body[i].y][piece->body[i].x].b = piece->color.b / 3;
	}
}
