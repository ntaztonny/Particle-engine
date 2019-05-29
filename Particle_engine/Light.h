
#ifndef LIGHT_H
#define LIGHT_H


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
#include <vector>



using std::vector;


enum LIGHT_TYPE
{
	LIGHT_SPOT,
	LIGHT_POINT,
	LIGHT_DIRECTIONAL
};


class Light
{

public:
	static int numLights;
	static vector<Light *> lights;
	static vector<int> availableLights;

	static void lightInit();
	Light(LIGHT_TYPE type);
	~Light();

	GLvoid visible(bool value);
	GLvoid setAmbient(float r, float g, float b, float a);
	GLvoid setDiffuse(float r, float g, float b, float a);
	GLvoid setSpecular(float r, float g, float b, float a);
	GLvoid setSpotDirection(float x, float y, float z);
	GLvoid setPosition(float x, float y, float z);
	GLvoid setCutOff(float value);
	GLvoid setSpotExponent(float value);
	GLvoid setAttenuation(float linear, float constant, float quadratic);
	void updateLight(void);
	void setLightType(LIGHT_TYPE type);
	

private:

	float ambient[4];
	float diffuse[4];
	float specular[4];
	float spotDirection[4];
	float position[4];
	float cutOff;
	float spotExponent;

	//int constant, linear, quadratic;
	int lightNum;
	bool visibility;

	int getNumLights(void);
	
	






};

#endif