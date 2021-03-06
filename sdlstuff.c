// global includes
#include "SDL.h"

//local includes
#include "globaldefs.h"
#include "sdlstuff.h"
#include "glstuff.h"
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
                        case SDL_KEYDOWN:
                                sdlHandleKeyPress(&event.key.keysym);
                        break;
		}

	}
	return TRUE;
}
void sdlHandleKeyPress(SDL_keysym *keysym){

        //todo add stuff to this and input.c
        switch (keysym->sym){
                case SDLK_ESCAPE:
                        SDL_Quit();
			exit(TRUE);
                break;
                case SDLK_SPACE:
                        active =!active;
                break;
                case SDLK_RIGHT:
                        skip = ((skip+1)*10.0)-1;
			printf("frameskip: %i\n", skip);
                break;
                case SDLK_LEFT:
                        skip = ((skip+1)/10.0)-1;
			if(skip <0) skip = 0;
			printf("frameskip: %i\n", skip);
                break;
                case SDLK_RIGHTBRACKET:
                        slowness = ((slowness)*2.0);
			printf("slowness: %i\n", slowness);
                break;
                case SDLK_LEFTBRACKET:
                        slowness = ((slowness)/2.0);
			if(slowness <1) slowness = 1;
			printf("slowness: %i\n", slowness);
                break;
                case SDLK_UP:
                        zoom*=2;
			printf("zoom: %f\n", zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);
                break;
                case SDLK_DOWN:
                        zoom/=2;
			printf("zoom: %f\n", zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);
                break;
                case SDLK_r:
                        zoom= 1;
			printf("zoom: %f\n", zoom);
			viewposx = 0;
			viewposy = 0;
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);
                break;
                case SDLK_w:
			viewposy += -0.5/sqrt(zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);

                break;
                case SDLK_s:
			viewposy += 0.5/sqrt(zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);

                break;
                case SDLK_a:
			viewposx += 0.5/sqrt(zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);

                break;
                case SDLK_d:
			viewposx += -0.5/sqrt(zoom);
			glDrawScreen(TRUE);
			glDrawScreen(TRUE);

                break;
		default:
		break;

        }
        return;
}

int sdlImportImage(const char * filename, int *height, int *width, void ** data){
	SDL_Surface *TextureImage;
	if(!(TextureImage = SDL_LoadBMP(filename))) return FALSE;
	*height = TextureImage->h;
	*width = TextureImage->w;
	int size = TextureImage->w * TextureImage->h * TextureImage->format->BytesPerPixel;
	*data = malloc(size);
	memcpy(*data, TextureImage->pixels, size);
	SDL_FreeSurface(TextureImage);
	return TRUE;
}
