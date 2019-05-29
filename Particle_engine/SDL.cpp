
#include "SDL.h"

#include <stdio.h> 
#include <string>
#include <math.h>
#include "GLEngine.h"
#include "Button.h"
#include <list>
#include "ListBox.h"
#include "Slider.h"
#include"Emitter.h"

using std::string;
using std::list;

const GLsizei winWidth = 800;
const GLsizei winHeight = 800;


Uint8  *keys = NULL;

GLfloat rotateY = 45.0;
GLfloat rotateX = 45.0;
GLfloat zoom = -85;
const float rotateSpeed = 0.5f;
const float zoomSpeed  = 0.1f;

char title[80];

Light *mainLight = NULL;
Texture *tex = NULL;
Control *controlled = NULL;
Emitter * emitter = NULL;

bool navigating = false;


MouseState state;

GLvoid establishProjection(GLsizei width, GLsizei height) // 3d/ projection view
{
	glViewport (0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, GLfloat(width)/GLfloat(height), 0.1f, 200.0f);

}

GLvoid setOrtho(GLsizei width, GLsizei height) // 2D view
{
	glViewport (0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,height,0 );

}

GLvoid initGL (GLsizei width, GLsizei height) // initilizes OpenGL state
{
	iEngine->initilize(width, height);
	establishProjection(width, height);
	 
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);    
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	// set light, texture and emitter
	mainLight = new Light(LIGHT_SPOT);
	mainLight ->setDiffuse(0.0, 0.0, 0.0, 1.0);
	mainLight ->setPosition(1.0, 20.0, 0.0);
	mainLight ->setSpotExponent(25);
	mainLight ->setCutOff(60);
	tex = new Texture("fire.tga", "texture");
	
	// Starting the particle system here, remember to call the emitter-> update function in the program loop (update) ||
	// I have done this in the drasceen function that will need time and an initialized GL state
	emitter = new Emitter();
	emitter ->setTexture(tex);
	emitter ->saturation = 0.56f;
	emitter -> alpha = 0.1f;
	emitter ->emissionRadius =  2.0f;
	emitter ->emissionRate = 200.0f;
	emitter ->sizeRange = 1.5f;
	emitter ->size = 2.0f;
	emitter->rotation.b = 10.0f;
	
	
}  

GLvoid Cube(GLvoid) // draws cube
{
	glBindTexture(GL_TEXTURE_2D, tex ->texID);
	//glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	//top face
		
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);

		//bottom face
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

		//front face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.0f, -1.0f,  1.0f);

		//back face
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f, -1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f,  1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0f,  1.0f,  -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.0f, -1.0f,  -1.0f);

		//left face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f, -1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f,  1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.0f,  1.0f,   1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.0f, -1.0f,   1.0f);

		//right face
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,   1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,   1.0f);

	glEnd();

	
}

GLvoid Plane(GLvoid) // draws plane
	{
		float width = 80.0f;
		float height = 80.0f;
		
		int divisions = 600;

		float incX = width/(float)divisions;
		float incY = height/(float)divisions;

		glNormal3f(0.0f,1.0f,0.0f);
		for(float x = -(width/2.0f); x < width/2.0f; x += incX)
		{
				for(float y = -(height/2.0f); y < height/2.0f; y += incY)
				{
					glBegin(GL_TRIANGLE_STRIP);	
						glVertex3f(x + incX, 0.0f,  y + incY);
						glVertex3f(x,        0.0f,  y + incY);
						glVertex3f(x + incX, 0.0f,  y);
						glVertex3f(x,        0.0f,  y);
					glEnd();
				}
		}
	
	}

GLvoid displayFPS() // sets window title 
{
	static long oldTime = SDL_GetTicks();
	static long loops = 0;
	static GLfloat FPS = 0;

	int newTime = SDL_GetTicks();

	if (newTime - oldTime > 1000)
	{	
		float newFPS =  (float)loops/float(newTime - oldTime) * 1000.0f;
		FPS = (newFPS + FPS)/2.0f;
		
		oldTime = newTime;
	loops = 0;

	sprintf_s(title, "Particle Engine - % f fps", FPS);
	
	}

	SDL_WM_SetCaption(title, NULL);
	
	loops++; 
	
		
}


GLvoid DrawScene(GLvoid) // Draws objects in the scene: particles, 
{	
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	establishProjection(winWidth, winHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   

	glDisable(GL_BLEND);
	glTranslatef(0.0f, 0.0f, zoom);
	glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateX, 0.0f, 1.0f, 0.0f);

	for (int i = 0; i < (int)Light::lights.size(); i++ ) // update created lights depending on view in our world
	{	
		Light::lights[i]-> updateLight();
	}
		
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	Plane();

	glEnable(GL_BLEND);
	emitter -> update(SDL_GetTicks());

	//Set the 2D mode here to draw text, projection pass 2

	glDisable(GL_LIGHTING);

	setOrtho(winWidth, winHeight);
	displayFPS();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// drawing controls for buttons, listbox, and sliders
	for(list<Control *>::iterator it = Control::controls.begin(); it != Control::controls.end(); it ++)
	{
		Control *control = (*it);

		control -> drawControl();
		if ((controlled != control && controlled != NULL) || navigating)
			continue;

		if(control->updateControl(state))
		{
			controlled = control;
			navigating = false;
			// gets to handle all the events
		}
		else if(control == controlled)
		{
			controlled = NULL;
			//Done handling events
		}
		else
		{	
			// updating is done.
		}
	
	}
	

	glFlush();
	SDL_GL_SwapBuffers();
	
}


//================handle keyboard input=========================
GLvoid KeyboardDown(unsigned char name, int x, int y)
{
	 keys[name] = true;
}

GLvoid KeyboardUp(unsigned char name, int x, int y)
{
	keys[name] = false;
}

GLvoid KeyboardSpecialDown(int name, int x, int y)
{
	keys[name] = true;
}

GLvoid KeyboardSpecialUp(int name, int x, int y)
{
	keys[name] = false;
}

//====================handle mouse input===============================
GLboolean updateNavigation(GLvoid)
{
	static int lastX = -1;
	static int lastY = -1;

	
	if(lastX == -1 && lastY == -1)
	{
		lastX = state.mousex;
		lastY = state.mousey;
	}

	int changeX = lastX - state.mousex;
	int changeY = lastY - state.mousey;
	

	lastX = state.mousex;
	lastY = state.mousey;

	if (state.leftMouseButton && controlled ==NULL)
	{
		SDL_WM_GrabInput(SDL_GRAB_ON);
		rotateX -= (float)changeX * rotateSpeed;;
		rotateY -= (float)changeY * rotateSpeed;

		if (rotateY < 1.0f)
			rotateY = 1.0f;

		navigating = true;
	
	}

	else if (state.rightMouseButton && controlled == NULL)
	{	
		SDL_WM_GrabInput(SDL_GRAB_ON);
		zoom -= changeX * zoomSpeed;
		navigating = true;
	
	}
	else
	{	
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		navigating = false; 
	
	}
	
	if (keys[SDLK_UP])
		rotateY -= 1;

	if (keys[SDLK_DOWN])
		rotateY += 1;

	if (keys[SDLK_RIGHT])
		rotateX -= 1;

	if (keys[SDLK_LEFT])
		rotateX += 1;
	if (keys[SDLK_ESCAPE])
		return true;
	return false;

}



int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// print out error: Failed to initilize SDL
	
	} 

	if ((SDL_SetVideoMode(winWidth, winHeight, 0, SDL_OPENGL) == NULL))
	{
	
		// print out error: Failed to initilize OpenGL
	}
	
	initGL( winWidth, winHeight); 

	int done = 0;

	while(!done)
	{	
		SDL_GetMouseState(&state.mousex, &state.mousey);

		state.leftMouseButton =		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
		state.rightMouseButton =	SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
		state.middleMouseButton =	SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
		
		DrawScene();
		
		 SDL_Event event;
		while(SDL_PollEvent (&event))
		{
			if (event.type == SDL_QUIT)
				done = 1;
			keys = SDL_GetKeyState(NULL);
			
		}
		if(updateNavigation())
			done = 1;
			
	}

	// Free the allocated memory
	for(list<Control *>::iterator it = Control::controls.begin(); it != Control::controls.end(); it ++) //controls
	{
		delete (*it);
		it = Control::controls.begin();
		
	}

	GLEngine::uninitilize(); // lights and textures in GLengine.cpp
	SDL_Quit();


return 0;
}