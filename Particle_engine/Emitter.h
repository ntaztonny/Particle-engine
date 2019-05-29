
#ifndef EMITTER_H
#define EMITTER_H
#include "Texture.h"
#include "Particle.h"
#include <list>

using std::list;


class Emitter
{

public:
	Emitter();
	~Emitter();
	void update(long time);
	void setTexture(Texture *texture);

	// variables
	list<Particle *> particles;
	Texture *texture;
	long lastTime;

	// attributes ============================
	float emissionRate;
	float emissionRadius;


	float size;
	float sizeRange;
	float life;
	float lifeRange;
	float saturation;
	float alpha;
	float spread;
	float gravity;
	
	Vector3	 position;
	Vector3  rotation;
	Vector3  wind;

protected:
	void addParticle(void);
	float frand(float start = 0, float end = 1);
};


#endif