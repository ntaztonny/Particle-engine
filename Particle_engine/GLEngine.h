#ifndef GLENGINE_H
#define GLENGINE_H

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN 
    #include <windows.h>
#endif

#if defined(__APPLE__) && defined (__MAC__)
	#include<OpenGL/gl.h>
	#include<OpenGL/glu.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
#endif

#include "Texture.h"
#include "Light.h"

#define iEngine GLEngine::getEngine()  

const int fontsize = 13;
const int fontSpace = 7;


class GLEngine
{
public: 
	//------------GLEngine functions----------------------------
	GLEngine();
	~GLEngine();
	GLvoid initilize(GLint width, GLint height);
	static GLEngine* getEngine(GLvoid);
	static GLvoid uninitilize(GLvoid);

	//---------------Texture for the text----------------
	GLvoid buildTexture(GLvoid);
	GLvoid drawText(GLint x, GLint y, const char * text, ...);
	GLuint getTextWidth(const char *text);
	GLuint getTextHeight(const char *text);

private:
	GLint fontBase;
	Texture *fontTexture;

};

#endif