
#include "Light.h"

int Light::numLights = 0;
vector<Light *> Light::lights ;
vector<int> Light::availableLights;

void Light::lightInit()
{
	 glGetIntegerv(GL_MAX_LIGHTS, &numLights);

	 for(int i = 0; i < numLights; i++)
		 availableLights.push_back(GL_LIGHT0 + i);
	 
}

Light::Light(LIGHT_TYPE type)
{
	lights.push_back(this);

	if(availableLights.size() > 0)
	{
		lightNum = availableLights[0];
		availableLights.erase(availableLights.begin());
		
		setLightType(type);
		visible(true);
		setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		setSpotDirection(0,-1,0);
		setPosition(0,0,0);
		setCutOff(45.0f);
		setSpotExponent(12.0f);
		updateLight();
	}
	else
	{
		lightNum = 0;
		visible(false);

	
	}

}
Light::~Light()
{	
	if(lightNum != 0)
	availableLights.push_back(lightNum);

	for(vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++)
		{if (*it == this)
			lights.erase(it);
	}

}

GLvoid Light::visible(bool value)
{
	visibility = value;

	if(visibility)
	{
		glEnable(lightNum);
	}
	else
		glDisable(lightNum);
}


GLvoid Light::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;

	glLightfv(lightNum, GL_AMBIENT, ambient);
}

GLvoid Light::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;

	glLightfv(lightNum, GL_DIFFUSE, diffuse);
}

GLvoid Light::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;

	glLightfv(lightNum, GL_SPECULAR, specular);
}

GLvoid Light::setSpotDirection(float x, float y, float z)
{
	spotDirection[0] = x;
	spotDirection[1] = y;
	spotDirection[2] = z;


	glLightfv(lightNum, GL_SPOT_DIRECTION, spotDirection);
}
GLvoid Light::setPosition(float x, float y, float z)
{	
	position[0] = x;
	position[1] = y;
	position[2] = z;


	glLightfv(lightNum, GL_POSITION, position);

}
GLvoid Light::setCutOff(float value)
{
	cutOff = value;
	glLightf(lightNum, GL_SPOT_CUTOFF, cutOff);


}
GLvoid Light::setSpotExponent(float value)
{
	spotExponent = value;
	glLightf(lightNum, GL_SPOT_EXPONENT, spotExponent);
}
GLvoid Light::setAttenuation(float linear, float constant, float quadratic)
{
	glLightf(lightNum, GL_LINEAR_ATTENUATION, linear);
	glLightf(lightNum, GL_CONSTANT_ATTENUATION, constant);
	glLightf(lightNum, GL_QUADRATIC_ATTENUATION, quadratic);
}

void Light::setLightType(LIGHT_TYPE type)
{

	if(type = LIGHT_SPOT)
	{
		position[3] = 1.0f;
	
	}
	else if(type = LIGHT_POINT)
	{
		position[3] = 1.0f;
		setCutOff(180);
	}
	else if(type = LIGHT_DIRECTIONAL)
	{
		position[3] = 0.0f;
	
	}
}

void Light::updateLight()
{
	glLightfv(lightNum, GL_POSITION, position);
	glLightfv(lightNum, GL_SPOT_DIRECTION, spotDirection);

}

int Light::getNumLights(void)
{
	return lightNum;

}