#include "GLEngine.h"


GLEngine::GLEngine()
{


}
	
GLEngine::~GLEngine()
{
	
	   
}
	
GLvoid GLEngine::initilize(GLint width, GLint height)
{
	Light::lightInit();
	fontTexture = new Texture("font.tga");
	buildTexture();
}
GLEngine* GLEngine::getEngine(GLvoid) 
{  
	static GLEngine* engine = new GLEngine();

	return engine;
}
GLvoid GLEngine::uninitilize(GLvoid)
{

	delete GLEngine::getEngine();
	
}

GLvoid GLEngine::buildTexture(GLvoid)
{	
	fontBase = glGenLists(256);

	glBindTexture(GL_TEXTURE_2D, fontTexture->texID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	for(int i = 0; i<256; i++)
	{	
		GLfloat cx = (float) (i%16)/16.0f;
		GLfloat cy = (float)(i/16)/16.0f;

		glNewList(fontBase +i, GL_COMPILE);

		glBegin(GL_QUADS);
		 
			glTexCoord2f(cx,			1-cy-0.0625f);		glVertex2i(0, fontsize);
			glTexCoord2f(cx + 0.0625f,	1-cy-0.0625f);		glVertex2i(fontsize, fontsize);
			glTexCoord2f(cx + 0.0625f,	1-cy);				glVertex2i(fontsize, 0);
			glTexCoord2f(cx,			1-cy);				glVertex2i(0, 0);
		glEnd();
		glTranslated(fontSpace, 0, 0);

		glEndList();

		
	
	}
}
GLvoid GLEngine::drawText(GLint x, GLint y, const char * in_text, ...)

{

	char text[256];

	va_list ap;

	va_start(ap, in_text);
		vsprintf_s(text, in_text, ap);
	va_end(ap);

	glEnable(GL_TEXTURE_2D);
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glBindTexture(GL_TEXTURE_2D, fontTexture->texID);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glTranslated(x, y, 0);

	glListBase(fontBase- 32);
	glCallLists((GLsizei)strlen(text), GL_BYTE, text);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

GLuint GLEngine::getTextWidth(const char * text)
{
	return GLuint (strlen(text)  * fontSpace);

}
	
GLuint GLEngine::getTextHeight(const char * text)
{
	return fontsize;
	
}