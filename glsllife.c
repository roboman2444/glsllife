//System includes

//local includes
#include "globaldefs.h"
#include "glsllife.h"
#include "sdlstuff.h"
#include "glstuff.h"
#include <unistd.h>
//main
extern int SDL_GetTicks();
int main(int argc, char *argv[]){
	debugmode = TRUE;
	active = FALSE;
	slowness = 1;
	skip = 0;
	zoom = 1.0f;
	int framecount, to, t;
	shadervertname = "./life.vert";
	shaderfragname = "./life.frag";
	playwidth = 2048;
	playheight = 2048;

	if(!sdlInit(1366, 768, 24) || !glInit()) return FALSE;
//	startsmall();
	if(argc >1)
		loadTexture(argv[1]);
	else startsmall();
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
			glDrawScreen(TRUE);
		}
//		sleep(1);
	if(slowness > 1)
		SDL_Delay(slowness);
	}
	return TRUE;
}
