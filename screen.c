#include "screen.h"
#include <stdlib.h>

void gotoxy(int x,int y){
	printf("\033[%d;%df",y,x);
}

void clearScreen(void){
	printf("\033[2J");
}

void setColor(unsigned char r, unsigned char g, unsigned char b){
	printf("\033[38;2;%u;%u;%um",r,g,b);
}

void setBackColor(unsigned char r, unsigned char g, unsigned char b){
	printf("\033[48;2;%u;%u;%um",r,g,b);
}

void resetColor(void){
	printf("\033[0m");
}

void setBold(void){
	printf("\033[1m");
}

void resetStyle(void){
	printf("\033[22m");
}

void setRaw(void){
	system("stty raw -echo");
}

void setCooked(void){
	system("stty cooked echo");
}
