/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

/*
 * Esta es una modificación de la librería que nos compartió el
 * profesor durante la clase. Contiene funciones que ayudan a
 * cambiar el color de los caracteres, a mover el cursor, y a borrar
 * la pantalla. También maneja las funciones que establecen el modo 
 * crudo y el input con límite de tiempo.
 *
 * Cabe resaltar que la mayoría de estas funciones son exclusivas
 * de Linux. 
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>

#define SIZE_X 104
#define SIZE_Y 26

void gotoxy(int x,int y);
void clearScreen(void);
void setColor(unsigned char r, unsigned char g, unsigned char b);
void setBackColor(unsigned char r, unsigned char g, unsigned char b);
void resetColor(void);
void setBold(void);
void resetStyle(void);
void setRaw(void);
void setCooked(void);
void setSpecialInput(void);
void setNormalInput(void);

#endif /* SCREEN_H */
