//System includes

//local includes
#include "globaldefs.h"
#include "glsllife.h"
#include "sdlstuff.h"
#include "glstuff.h"
#include <unistd.h>
//main
extern int SDL_GetTicks();
int main(int argc, char **argv){
	debugmode = TRUE;
	active = FALSE;
	skip = 0;
	int framecount, to, t;
	shadervertname = "./life.vert";
	shaderfragname = "./life.frag";
	if(!sdlInit(800, 600, 24) || !glInit()) return FALSE;
//	startsmall();
	loadTexture("acorn.bmp");
	to = SDL_GetTicks();
	while(TRUE){
		sdlCheckEvent();
		if(active){
			glRender();
			framecount++;
			if(framecount>999){
				t = SDL_GetTicks();
				printf("%f fps\n", 1000000.0f/(t-to)); // 100 frames * 1000 ticks
				to = t;
				framecount = 0;
			}
		} else {
			glDrawScreen();
		}
//		sleep(1);
	}
	return TRUE;
}
