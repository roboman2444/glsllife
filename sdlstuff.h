#ifndef SDLSTUFFHEADER
#define SDLSTUFFHEADER

//functions
int	resizeWindow(int width, int height, int bpp);
int	sdlCheckEvent(void);
int 	sdlImportImage(const char * filename, int *height, int *width, void ** data);

//vars
int	screenWidth, screenHeight, screenBPP;
int 	sdlInit(int width, int height, int bpp);

#endif
