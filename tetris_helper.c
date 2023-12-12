/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include "tetris_helper.h"

//Inicializa las posiciones, offsets de geración y los colores de los 7 tipos
//de tetromino por default. Esto es, esencialmente, cargar los 
//sprites de las piezas en memoria. Esto se hace únicamente al principio del 
//juego, y se guradan en un arreglo llamado defaultPositions.
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

	//Por default, cada pieza empieza en la casilla (4, 1) de la matriz, 
	//es decir, arriba en el centro.

	for(int i=0;i<7;i++){
		defaultPositions[i].body[0].x = 4;
		defaultPositions[i].body[0].y = 1;
		generatePiece(&defaultPositions[i]);
	}

}

//Utilizando el "centro" de las piezas y sus offsets de generación actuales, 
//guarda en la pieza la ubicación de cada uno de los pixels que la conforman.
void generatePiece(tetromino *piece){
	for(int i=1;i<4;i++){
		piece->body[i].x = piece->body[0].x + piece->generation_offset[i-1].x;
		piece->body[i].y = piece->body[0].y - piece->generation_offset[i-1].y;
	}
}

//Abajo se encuentran todas las funciones de rotación y traslación 
//de tetrominos. Hay una función que realiza un movimiento (i.e. rotar
//90° hacia la derecha) para todos los tipos de piezas.

//Nótese que las funciones de rotación y traslación no modifican la 
//pieza original, sino que regresa una copia.
//Esto es intencional, ya que queremos checar si el movimiento
//que vamos a hacer es legal o no.

//FUNCIONES DE ROTACIÓN
//Para rotar una pieza, cambiamos los offsets de generación de la misma,
//y luego la generamos. Por ejemplo, si los offsets de una pieza son
// ←, ↑, →, para rotar a la derecha los cambiamos a ↑, →, ↓.
// El centro de la pieza no se mueve durante las rotaciones.
//Los diagramas y cálculos para cada una de las rotaciones los hice en papel, y 
//me tomó un buen rato, pero no son difíciles de obtener.

//Rota 90° a la derecha.
tetromino rotateR(tetromino piece){
	for(int i=0;i<3;i++){
		char temp = piece.generation_offset[i].x; 
		piece.generation_offset[i].x = piece.generation_offset[i].y;
		piece.generation_offset[i].y = -1*temp;
	}
	generatePiece(&piece);
	return piece;
}

//Rota 90° a la izquierda.
tetromino rotateL(tetromino piece){
	for(int i=0;i<3;i++){
		char temp = piece.generation_offset[i].x; 
		piece.generation_offset[i].x = -1 * piece.generation_offset[i].y;
		piece.generation_offset[i].y = temp;
	}
	generatePiece(&piece);
	return piece;
}

//Rota 180°.
tetromino rotate2(tetromino piece){
	for(int i=0;i<3;i++){
		piece.generation_offset[i].x *= -1;
		piece.generation_offset[i].y *= -1;
	}
	generatePiece(&piece);
	return piece;
}

//FUNCIONES DE TRASLACIÓN

//En contraste,las funciones de movimiento son muy sencillas.
//Simplemente movemos el centro de la pieza a la dirección que queremos,
//y generamos la pieza.

//Mueve la pieza una casilla hacia abajo.
tetromino fall(tetromino piece){
	piece.body[0].y++;
	generatePiece(&piece);
	return piece;
}

//Mueve la pieza una casilla hacia la derecha.
tetromino moveR(tetromino piece){
	piece.body[0].x++;
	generatePiece(&piece);
	return piece;
}

//Mueve la pieza una casilla hacia la izquierda.
tetromino moveL(tetromino piece){
	piece.body[0].x--;
	generatePiece(&piece);
	return piece;
}

//FUNCIONES PARA CHECAR SI LOS MOVIMIENTOS SON LEGALES:

//Verifica si una casilla está vacía, mediante el color.
//Los tetrominos tienen colores muy brillantes, así que 0x80 es el 
//mínimo en alguno de los canales (en el morado de la pieza T).
//Entonces, cualquier pixel con menos intensidad que eso
//está vacío.
//No checamos si el pixel es exactamente negro por las sombras de las piezas:
//Son pixeles de colores, pero deberían considerarse vacíos.
unsigned char isEmpty(unsigned char x, unsigned char y){
	return (matrix[y][x].r | matrix[y][x].g | matrix[y][x].b) >= 0x80;
}

//Esta función checa que todos los pixeles que conforman una pieza estén dentro
//de la matriz y que no colisionen con otras piezas.
//Nótese que si la pieza actual estuviera guardada en la matriz, esto fallaría
//siempre, así que antes de hacer este chequeo, tenemos que borrar la pieza
//con erasePiece. Si el movimiento es legal, podemos dibujar la nueva pieza, 
//y si no, la restauramos.
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
	while (legalPiece(&possible)){
			possible = fall(possible);
	}
	possible.body[0].y--;
	generatePiece(&possible);
	drawPiece(&piece);
	return possible;
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
		response = fall(response);
		updateQueue();
		drawInHold(currentHold);
		count++;
		return response;
	}
	response = fall(currentHold);
	currentHold = defaultPositions[piece.id];
	drawInHold(currentHold);
	return response;
}
