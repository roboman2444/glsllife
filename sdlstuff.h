#ifndef SDLSTUFFHEADER
#define SDLSTUFFHEADER

//functions
int	resizeWindow(int width, int height, int bpp);
int	sdlCheckEvent(void);

//vars
int	screenWidth, screenHeight, screenBPP;
int 	sdlInit(int width, int height, int bpp);

#endif
