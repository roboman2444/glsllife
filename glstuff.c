//global includes
#include <GL/glew.h>
#include <GL/gl.h>
#include "SDL.h"

//local includes
#include "globaldefs.h"
#include "sdlstuff.h" //todo something this
#include "shaderstuff.h"

//local vars
GLuint texid2, texid1;
GLuint fbid2, fbid1;
int which = FALSE;
//functions
int initFB(void){
	glGenTextures(1, &texid1);
	glBindTexture(GL_TEXTURE_2D, texid1);
	//may need to change gl_int to byte or something fo speed
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_POINT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screenWidth, screenHeight, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenFramebuffers(1, &fbid1);
	glBindFramebuffer(GL_FRAMEBUFFER, fbid1);
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, texid1, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);//unbind
	if(debugmode) printf("DEBUG -- Bound framebuffer1 to: %i and texture to : %i \n", fbid1, texid1);
	glGenTextures(1, &texid2);
	glBindTexture(GL_TEXTURE_2D, texid2);
	//may need to change gl_int to byte or something fo speed
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_POINT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screenWidth, screenHeight, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenFramebuffers(1, &fbid2);
	glBindFramebuffer(GL_FRAMEBUFFER, fbid2);
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, texid2, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);//unbind
	if(debugmode) printf("DEBUG -- Bound framebuffer2 to: %i and texture to : %i \n", fbid2, texid2);
	//todo error detection
	return TRUE;
}
int glInit(void){
	if(debugmode) printf("DEBUG -- Initialising OpenGL \n");


	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ){
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
		return FALSE;
	}
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	glEnable(GL_TEXTURE_2D);

	//todo move this stuff

	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);// Select The Projection Matrix
	glLoadIdentity();// Reset The Projection Matrix
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); //maybe change
	glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
	glLoadIdentity();                           // Reset The Modelview Matrix

	glColor3f(1.0f, 1.0f, 1.0f); //wont need this much longer


	//todo error checkelecking
	if(!initShader()) return FALSE;
	if(!initFB())	return FALSE;
	return TRUE;
}
void drawfsquad(void){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f,-1.0f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f( 1.0f,-1.0f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f( 1.0f, 1.0f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, 1.0f, -0.5f);
	glEnd();
}
void drawsmallquad(const float sizex, const float sizey){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-sizex,-sizey, -0.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f( sizex,-sizey, -0.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f( sizex, sizey, -0.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-sizex, sizey, -0.5f);
	glEnd();
}
void startsmall(void){
	glBindFramebuffer(GL_FRAMEBUFFER, fbid2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f); //wont need this much longer
	drawsmallquad(0.1f, 0.1f);
}
int glRender(void){
	//todo
	if(which)glBindFramebuffer(GL_FRAMEBUFFER, fbid2);
	else glBindFramebuffer(GL_FRAMEBUFFER, fbid1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glUseProgram(programobject);

	if(which)glBindTexture(GL_TEXTURE_2D, texid1);
	else glBindTexture(GL_TEXTURE_2D, texid2);
	drawfsquad();


	if(which)glBindTexture(GL_TEXTURE_2D, texid2);
	else glBindTexture(GL_TEXTURE_2D, texid1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	drawfsquad();
	//todo make this cleaner
	SDL_GL_SwapBuffers();
	which = !which;
	//todo errorcheckin
	return TRUE;
}
