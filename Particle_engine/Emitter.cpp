
#include "Emitter.h" 

Emitter::Emitter()
{
	texture = NULL;
	lastTime = -1;
	emissionRate = 30.0f;
	emissionRadius = 0.0f;
	   
	life = 2.0f;
	lifeRange = 0.5f;

	size = 5.0f;
	sizeRange = 2.0f;

	saturation = 1.0f;
	alpha = 0.5;

	spread =  1.0f;
	gravity = 0.0f;

}

Emitter::~Emitter()
{
	for(list<Particle *>::iterator it = particles.begin(); it != particles.end(); it++ )
	{
		delete(*it);
	
	}

}
void Emitter::update(long time)
{	 
	
	if (texture == NULL)
		exit(0);

	if (lastTime == -1)
		lastTime = time;

	int numEmission = (int) (float(time - lastTime)/ 1000.0f * emissionRate);

	for(int i = 0; i< numEmission; i++ )
		addParticle();

	if(numEmission > 0)
		lastTime = time;

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(position.a, position.b, position.c);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->texID);

	for(list<Particle *>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		Particle *particle = (*it);

		particle ->  acceleration.b = -gravity;
		particle ->  acceleration += wind;
		particle ->  alpha = alpha;
		particle ->  rotation = rotation;

		particle -> Update(time);

		// This line may cause a program crush, it accesses and invalid iterator
		/*if(particle -> active == false)
		{
			delete particle;
			list<Particle *>::iterator pTemp = it--;
			particles.erase(pTemp);
		
		}*/

		glMatrixMode(GL_MODELVIEW); 
		glPopMatrix();
	
	}


}
void Emitter::setTexture(Texture *tex)
{
	texture = tex;
}

void Emitter::addParticle(void)
{
	Particle *particle = new Particle (int(particles.size()));
	float r =  frand() * saturation +(1 - saturation);
	float g =  frand() * saturation +(1 - saturation);
	float b =  frand() * saturation +(1 - saturation);

	particle -> color = Vector3(r,g,b);

	particle -> life =  frand(life -lifeRange, life + lifeRange);
	particle -> totalLife = particle -> life;


	particle -> velocity = Vector3(frand(-spread, spread), frand(3, 20), frand(-spread, spread));
	particle -> acceleration = Vector3(0, -gravity, 0);

	particle -> size = frand( size - sizeRange, size + sizeRange);

	particle -> position.a = frand (-emissionRadius, emissionRadius);
	particle -> position.c = frand (-emissionRadius, emissionRadius);

	particles.push_back(particle);

}

float Emitter::frand(float start, float end)
{
	float num = (float)rand()/ float(RAND_MAX);

	return(num * (end - start) + start);

}