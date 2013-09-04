// global imports
#include <GL/glew.h>
#include <GL/gl.h>
#include <string.h>

//local includes
#include "globaldefs.h"
#include "shaderstuff.h"
#include "filestuff.h"
extern int printLogStatus(int shader);
int initShader(void){
	if(debugmode) printf("DEBUG -- Initializing Shaders\n");
	char * shadervertstring;
	char * shaderfragstring;
	int shadervertlength, shaderfraglength;
	if(shadervertname){
		loadfilestring(shadervertname, &shadervertstring, &shadervertlength);
		if(debugmode)printf("DEBUG -- Vert shader loaded with size %i and contents: \n %s \n", shadervertlength, shadervertstring);

	} else {
		fprintf(stderr, "ERROR -- No vertex shader! \n");
		return FALSE;
	}
	if(shaderfragname){
		loadfilestring(shaderfragname, &shaderfragstring, &shaderfraglength);
		if(debugmode)printf("DEBUG -- Frag shader loaded with size %i and contents: \n %s \n", shaderfraglength, shaderfragstring);

	} else {
		fprintf(stderr, "ERROR -- No fragment shader! \n");
		return FALSE;
	}

	GLuint vertshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);
	if(debugmode) printf("DEBUG -- Shaders created at %i and %i\n", vertshader, fragshader);


	glShaderSource(vertshader, 1, (const GLchar **)shadervertstring, &shadervertlength+1);
	glShaderSource(fragshader, 1, (const GLchar **)shaderfragstring, &shaderfraglength+1);


	glCompileShader(vertshader);
	glCompileShader(fragshader);
	free(shadervertstring);
	free(shaderfragstring);
	//todo error check


	GLint fragcompiled, vertcompiled;
	glGetShaderiv(vertshader, GL_COMPILE_STATUS, &vertcompiled);
	glGetShaderiv(fragshader, GL_COMPILE_STATUS, &fragcompiled);
	printLogStatus(vertshader);
	printLogStatus(fragshader);
	if (!vertcompiled)printLogStatus(vertshader);
	if (!fragcompiled)printLogStatus(fragshader);
	if (!vertcompiled || !fragcompiled){
		fprintf(stderr, "ERROR -- shader compilation failed \n");
		return FALSE;
	}



	programobject = glCreateProgram();
	glAttachShader(programobject, vertshader);
	glAttachShader(programobject, fragshader);
	glLinkProgram(programobject);
	glValidateProgram(programobject);
	if(debugmode) printf("DEBUG -- Shader compiled and linked \n");
	//todo error checking
	return TRUE;
}
int printLogStatus(int shader){
	GLint blen = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &blen);
	if (blen > 1){
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(shader, blen, 0, compiler_log);
		fprintf(stderr, "compiler_log: %s \n", compiler_log);
		free(compiler_log);
	}
	return TRUE;
}
