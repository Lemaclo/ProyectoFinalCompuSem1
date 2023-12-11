/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
Licenciatura en Computación Matemática, Semestre 1
Elementos de Ciencias de la Computación
Profesor Alonso Ramirez
Proyecto Final
*/

#include "screen.h"
#include <stdlib.h>

//Cambia la posicón del cursor en la pantalla.
void gotoxy(int x,int y){
	printf("\033[%d;%df",y,x);
}

//Borra todos los caracteres de la pantalla.
void clearScreen(void){
	//system("clear");
	printf("\033[2J");
}

//Cambia el color del los caracteres que se imprimen con printf.
//Admite cualquier combinación RGB.
void setColor(unsigned char r, unsigned char g, unsigned char b){
	printf("\033[38;2;%u;%u;%um",r,g,b);
}

//Cambia el color del fondo de los caracteres que se imprimen.
void setBackColor(unsigned char r, unsigned char g, unsigned char b){
	printf("\033[48;2;%u;%u;%um",r,g,b);
}

//Reestablece el color de los caracteres por default (blanco).
void resetColor(void){
	printf("\033[0m");
}

//Cambia los caracteres a negritas.
void setBold(void){
	printf("\033[1m");
}

//Cambia los caracteres a estilo nomal.
void resetStyle(void){
	printf("\033[22m");
}

//Habilita el modo crudo de la terminal.
void setRaw(void){
	system("stty raw -echo");
}

//Deshabilita el modo crudo de la terminal.
void setCooked(void){
	system("stty cooked echo");
}

//Esto habilita el input con límite de tiempo, y
//hace que el cursor deje de parpadear.
//Si esto está habilitado, getchar() espera 
//una décima de segundo para recibir input, y si 
//no recibe nada, devuelve -1. 
//Esta función es necesaria para que las piezas puedan caer, 
//incluso si el usuario no ingresa nada de input.
void setSpecialInput(void){
	system("stty min 0 time 1");
	system("tput civis");
}

//Esta función revierte la anterior.
void setNormalInput(void){
	system("stty min 1 time 0");
	system("tput cnorm");
}
