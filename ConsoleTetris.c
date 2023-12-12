/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

/* Este es el archivo principal.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//La única razón para que esta librería esté aquí es para
//reproducir música.
#include <pthread.h>
#include "screen.h"
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

//Me pareció que estas son las funciones que pueden quedarse en el archivo principal,
//pues son las que pueden ser modificadas más a menudo.
tetromino manageInput(int input, tetromino piece, 
		int *count, tetromino *shadow, int *holdRight);

void updateScore(unsigned long *score, unsigned char linesCleared, int timer);

//Esta función únicamente reproduce música.
void *playMusic(void *);

tetromino cola[14];

int main(int nargs, char **argsv){
	//Se utilizan para reproducir la música en paralelo al juego.
	//No entiendo del todo cómo funcionan los threads, pero 
	//esto fue lo que se me ocurrió hacer.
	pthread_t music;
	pthread_create(&music, NULL, playMusic, NULL);

	//Inicializa las variables, y los espacios de dibujo
	init(nargs, argsv);
	
	//Son las variavles y flags que necesita el juego.
	//count y timer se usan para definir la velocidad del juego,
	//set es una flag para cuando una pieza fija su posición, 
	//y holdRight es una flag que indica si se puede realizar o 
	//no el hold (Se puede hacer una vez por cada pieza nueva de la cola).
	int input, count, timer, set, holdRight;
	unsigned long score = 0;
	//Piece es la pieza que controlamos, shadow es su sombra, 
	//y possible es la pieza que resulta del movimiento del usuario.
	tetromino piece, possible, shadow;
	count = set = holdRight = 1;
	//Mientras más alto sea timer, más lento va el juego. Puede bajar hasta 1.
	timer = 10;
	//El número 3 representa Ctrl+C, que se usa para terminar el juego antes.
	while((input = getchar()) != 3){
		//Primero checa si la pieza actual ya fijó su posición.
		if (set){	
			//Si es el caso, borra las líneas que se llenaron, 
			//actualiza el puntaje, y obtiene una nueva pieza.
			//También actualiza timer en función del score.
			//Mientras más alto sea el score, más bajo es el timer, 
			//pero nunca baja de 1.
			unsigned char lines = clearLines();
			updateScore(&score, lines, timer);
			timer = 10 - (int)log2f((score/1000) + 1);
			timer = timer >= 1 ? timer : 1;
			piece = pop();
			updateQueue();
			//Siempre que generamos una nueva pieza, lo primero que hace es
			//intentar caer un espacio.
			possible = fall(piece);
			if(legalPiece(&possible)){
				piece = possible;
			} else {
				//Si la pieza nueva que obtendríamos no puede caer ni 
				//una vez, significa que hemos bloqueado la parte de arriba 
				//de la matriz, y por lo tanto, hemos perdido el juego.
				break;
			}
			draw(&piece, &shadow, holdRight, score);
			//Cuando acabamos esto, reiniciamos las flags.
			set = 0;
			holdRight = 1;
		}
		//Obtenemos la pieza que genera el movimiento que el usuario
		//ingresó.
		possible = manageInput(input, piece, &count, &shadow, &holdRight);
		//Luego, queremos ver si el movimiento que resulta es legal, es decir
		//que no se sale de la matriz y que no ocupa el espacio de otras
		//piezas.
		erasePiece(&piece);
		if(legalPiece(&possible)){
			//Si es legal, la pieza actual se mueve.
			piece = possible;
		}
		//Cada cierto tiempo, la pieza va a intentar caer, sin intervención del usuario.
		//Este tiempo depende de count y timer.
		if(count % timer == 0){
			possible = fall(piece);
			erasePiece(&piece);
			//Si la pieza no puede caer, entonces se fija su posición, 
			//con el condicional del principio del bucle.
			if(legalPiece(&possible)){
				piece = possible;
			} else {
				set = 1;
			}
		}
		erasePiece(&shadow);
		//Por último, se imprimen todas las zonas de dibujo actualizadas.
		draw(&piece, &shadow, holdRight, score);
		//Y también incrementamos count
		count++;
	}
	//Al final, reestablecemos las configuraciones de la terminal, 
	//limpiamos la pantalla, e imprimimos el score final del usuario.
	cleanUp(score);
	pthread_join(music, NULL);
	return 0;
}

//Esta función maneja todo el input del usuario.
//Los controles son completamente arbitrarios, los escogí por
//que así me acostumbré a jugar.
tetromino manageInput(int input, tetromino piece, int *count, tetromino *shadow, int *holdRight){
	switch(input){
		//La tecla 'a' mueve a la izquierda
		case 'a':
			return moveL(piece);
		//La tecla 'd' mueve a la derecha
		case 'd':
			return moveR(piece);
		//La tecla 's' mueve hacia abajo lento (soft drop)
		//(lo hace forzando una caida)
		case 's':
			*count = 0;
			return piece;
		//Y la tecla 'w' hace la caída instantánea (hard drop)
		case 'w':
			*count = 0;
			return *shadow;
		//Esto es para las flechas.
		case 27:
			if(getchar() == 91){
				switch(getchar()){
					//La flecha izquierda rota 90° a la izquierda
					case 68:
						return rotateL(piece);
					//La flecha derecha rota 90° a la dercha
					case 67:
						return rotateR(piece);
					//La flecha abajo rota 180°
					case 66:
						return rotate2(piece);
					//La flecha arriba utiliza el hold.
					//(si tenemos derecho)
					case 65:
						if (*holdRight){
							*holdRight = 0;
							return holdPiece(piece);
						}
					default:
						break;
				}
			}
		//Con la configuración de input que realiza setSpecialInput() en 
		//screen.c, getchar devuelve -1 si han pasado 0.1 segundos sin recibir input
		//del usuario.
		case -1:
			//En ese caso, es necesaria esta línea para que se pueda volver 
			//a recibir input.
			rewind(stdin);
			//Y además, no hacemos ningún cambio a la pieza actual.
			return piece;
		default:
			return piece;
	}
}

//Esta función maneja la puntuación. Para ser sincero, el sistema de puntuación que
//implementé es completamente arbitrario y se parece muy poco al de tetris.
//Me pareció divertido darle valores propios a borrar 1, 2, 3, o 4 líneas,
//así como los bonus por hacer varias líneas seguidas y por la dificultad.
//Sin embargo, repito que un puntaje de 10000 aquí no refleja el mismo puntaje
//en el juego original.
void updateScore(unsigned long *score, unsigned char linesCleared, int timer){
	static unsigned char combo;
	unsigned int points = 0;
	switch (linesCleared){
		case 0:
			//Si no hacemos ninguna línea, reiniciamos el contador de combo, 
			//y no modificamos el puntaje.
			combo = 1;
			return;
		case 1:
			//Si hacemos una línea ganamos 100 puntos de base...
			points += 100;
			break;
		case 2:
			//...dos líneas son 300,...
			points += 300;
			break;
		case 3:
			//...tres son 500,...
			points += 500;
			break;
		case 4:
			//...y cuatro son 1000.
			points += 1000;
			break;
		default:
			//Debería ser imposible hacer algo que no sean 0,1,2,3, o 4 líneas, así
			//que hay una penalización por hacer trampa (también sirve para
			//indicar que algo no está bien con el código).
			points -= 1000000;
			break;
	}
	//Los puntos base que obtenemos se multiplican según la dificultad
	//(recodemos que timer alto es baja dificultad y viceversa). Timer tiene
	//un valor máximo de 10.
	points *= (11 - timer);
	//Además, si hacemos varias líneas consecutivas, también se multiplican los puntos
	//base.
	points *= combo;
	//El combo sigue mientras cada pieza limpie al menos una línea. Es increíble,
	//pero se pueden hacer combos más de 15.
	combo++;
	//Finalmente sumamos al puntaje lo que merecemos.
	*score += points;
}

//Esta función toca el archivo de música en paralelo al juego y en repetición.
//Tuve que instalar un paquete (sox) para tener disponible el comando play.
//Si jugamos alrededor de 40 minutos, la música termina.
void *playMusic(void *){
	system("play music.mp3 -q --multi-threaded repeat 32");
}
