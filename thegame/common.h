#include"MAIN.h"
#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define HANDLE_ERROR(msg)		printf(msg":%s\n", SDL_GetError());\
exit(EXIT_FAILURE);

typedef struct {//定义app结构，存放必要的全局变量
	SDL_Window* Window;
	SDL_Renderer* render;
	TTF_Font *font_title;
	SDL_Color color_title;
	SDL_Surface* surface_menu;
	SDL_Surface* surface_road;
	SDL_Surface *surface_title;
	SDL_Texture* texture_road;
	SDL_Texture* texture_menu;
	SDL_Texture* texture_title;
	SDL_Event event;
	SDL_Rect Road_rect[2];
	SDL_Rect rect_title;
	SDL_Event mainevent;

	Mix_Music *bgm;
	Mix_Chunk *sound[5];
	bool* keyboard;
	
}App;

App app;
bool jump;
bool down;
bool crouch;
bool collision;
bool detect[3];
unsigned long score_m;
double rate;




#define Width_Window 475//宏定义也放入头文件中
#define Height_Window 246
#define V 5


#endif 


