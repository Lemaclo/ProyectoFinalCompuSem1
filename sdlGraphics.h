/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
	int x, y;
} mouse;

//Con esto, vamos a manejar todo el input
typedef struct{
	unsigned char up, down, left, right, space;
	unsigned char w, a, s, d;
	unsigned char mleft, mright;
	unsigned char close;
	mouse m;
} global_input;

//Ventana Global
extern SDL_Window *window;
//Renderer Global
extern SDL_Renderer *renderer;
//Input Global
extern global_input gin;

//Inicia SDL
int initialize();
//Libera toda la memoria utilizada
void terminate();

//Limpia la pantalla
void prepareScene();
//Dibuja la pantalla
void presentScene();

//Carga una imagen como textura
SDL_Texture *loadTexture(char *filename);
//Dibuja una textura
void blit(SDL_Texture *texture, int x, int y, float scale);

//Maneja el input
void manageInput();

