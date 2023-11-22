/*
Luis Emilio Martínez Capetillo
luis.capetillo@cimat.mx
*/

#include "sdlGraphics.h"

//Al principio, cualquier input es 0.
global_input gin;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initialize(){
	//Inicializamos SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("No se pudo inicializar SDL: Error %s\n", SDL_GetError());
		return 0;
	}
	//Creamos nuestra ventana
	window = SDL_CreateWindow("Mi ventana",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,700, 500, 0);
	if (window == NULL){
		printf("No se pudo crear la ventana. Error %s\n", SDL_GetError());
		return 0;
	}
	//Creamos el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL){
		printf("No se pudo inicializar el renderizador. Error %s\n", SDL_GetError());
		return 0;
	}
	//Permitimos el uso de PNG y JPG
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	//Inicializamos los inputs
	gin.up = 0;
	gin.down = 0;
	gin.left = 0;
	gin.right = 0;
	gin.space = 0;
	gin.w = 0;
	gin.a = 0;
	gin.s = 0;
	gin.d = 0;
	gin.mleft = 0;
	gin.mright = 0;
	gin.m.x = 0;
	gin.m.y = 0;
	gin.close = 0;
	return 1;
}

void terminate(){
	//Cerramos el programa
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture *loadTexture(char *filename){
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL){
		printf("Falló la carga de imagen. Error: %s\n", SDL_GetError());
	}
	return texture;
}

void prepareScene(void){
	//Preparativos antes de dibujar la pantalla
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
}

void presentScene(void){
	//Supongo que hace el trabajo duro
	SDL_RenderPresent(renderer);
}

//Carga texturas en posiciones
void blit(SDL_Texture *texture, int x, int y, float scale){
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w *= scale;
	dest.h *= scale;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void manageInput(){
	SDL_GetMouseState(&gin.m.x,&gin.m.y);
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0){
		switch (event.type){
			case SDL_QUIT:
				gin.close = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode){
					case SDL_SCANCODE_UP:
						gin.up = 1;
						break;
					case SDL_SCANCODE_DOWN:
						gin.down = 1;
						break;
					case SDL_SCANCODE_RIGHT:
						gin.right = 1;
						break;
					case SDL_SCANCODE_LEFT:
						gin.left = 1;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode){
					case SDL_SCANCODE_UP:
						gin.up = 0;
						break;
					case SDL_SCANCODE_DOWN:
						gin.down = 0;
						break;
					case SDL_SCANCODE_RIGHT:
						gin.right = 0;
						break;
					case SDL_SCANCODE_LEFT:
						gin.left = 0;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button){
					case SDL_BUTTON_RIGHT:
						gin.mright = 1;
						break;
					case SDL_BUTTON_LEFT:
						gin.mleft = 1;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button){
					case SDL_BUTTON_RIGHT:
						gin.mright = 0;
						break;
					case SDL_BUTTON_LEFT:
						gin.mleft = 0;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}
