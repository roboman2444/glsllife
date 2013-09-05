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
	int framecount, to, t;
	to = SDL_GetTicks();
	shadervertname = "./life.vert";
	shaderfragname = "./life.frag";
	if(!sdlInit(800, 600, 24) || !glInit()) return FALSE;
	startsmall();
	while(TRUE){
		glRender();
		sdlCheckEvent();
		framecount++;
		if(framecount>99){
			t = SDL_GetTicks();
			printf("%f fps\n", 100000.0f/(t-to)); // 100 frames * 1000 ticks
			to = t;
			framecount = 0;
		}
//		sleep(0.1);
	}
	return TRUE;
}
