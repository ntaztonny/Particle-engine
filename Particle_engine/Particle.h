
#ifndef PARTICLE_H
#define PARTICLE_H

#include "GLEngine.h"
#include "Vector3.h"

class Particle
{
public:
	Particle(int id);

	void Update (long time);


	// variables

	int id;
	long lastTime;

	float totalLife;
	float life;
	float alpha;
	float size;

	float bounciness;

	bool active;    


	Vector3 color;
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 rotation;


private:
	void rotate(float angle, float &y, float &z);


};


#endif