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
