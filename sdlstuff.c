// global includes
#include "SDL.h"

//local includes
#include "globaldefs.h"
#include "sdlstuff.h"

//local vars
SDL_Surface *surface;
const SDL_VideoInfo *videoInfo;
int videoFlags;

//functions
int	resizeWindow(int width, int height, int bpp){
	if(debugmode) printf("DEBUG -- SDL video resize to: %ix%i with %i bits per pixel \n", width, height, bpp);
	if(height<1) height = 1;
	if(width<1) width = 1;
	screenWidth = width;
	screenHeight = height;
	surface = SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, videoFlags);
	if(!surface){
		fprintf(stderr, "ERROR -- SDL video resize failed: %s \n", SDL_GetError());
		return FALSE;
	}
	return TRUE;
}
int sdlInit(int width, int height, int bpp){
	if(debugmode) printf("DEBUG -- SDL window initializing \n");
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr, "ERROR -- SDL video init failed: %s \n", SDL_GetError());
		return FALSE;
	}
	videoInfo = SDL_GetVideoInfo();
	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	videoFlags |= SDL_RESIZABLE;
	if(videoInfo->hw_available) videoFlags |= SDL_HWSURFACE;
	else			    videoFlags |= SDL_SWSURFACE;
	if(videoInfo->blit_hw) 	    videoFlags |= SDL_HWACCEL;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return resizeWindow(width, height, bpp);
}

int sdlCheckEvent(void){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				SDL_Quit();
				exit(TRUE);
			break;
		}

	}
	return TRUE;
}
