//This creates the environment in which the particles can be found.
#include "world.h"
//Constructor class for the world class
World::World(int width, int height) :width(width), height(height) 
{

}
//Deconstructor for the world class, which deletes all of the particles and spring forces
World::~World() 
{
	for (int i = 0; i < springForces.size(); i++)
	{
		delete springForces[i];
	}
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}
}
//This adds random particles to the world with random variables to determine how it'll interact with the world
Particles* World::addParticle()
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> sizeDist(10, 20);
	float size = sizeDist(rd);
	std::uniform_int_distribution<int> massDist(100, 10000);
	float mass = massDist(rd);
	std::uniform_int_distribution<int> xDist(size, width - size);
	float x = xDist(rd);
	std::uniform_int_distribution<int> yDist(size, height - size);
	float y = yDist(rd);
	std::uniform_real_distribution<float> speedDist(0, 1);
	float speed = speedDist(rd);
	std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
	float angle = angleDist(rd);
	std::uniform_real_distribution<float> elasticityDist(0.8, 1);
	float elasticity = elasticityDist(rd);

	return addParticle(x, y, size, mass, speed, angle, elasticity);
}
//This adds the particles to the world but works out the drag for the particles
Particles* World::addParticle(float x, float y, float size, float mass, float speed, float angle, float elasticity)
{
	float drag = pow((mass / (mass + airM)), size);
	Particles* particle = new Particles(x, y, size, mass, speed, angle, elasticity, drag);
	particles.push_back(particle);
	return particle;
}
//This gets the positions for the particles in the world by using a pointer to the particle class
Particles* World::getParticle(float x, float y)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (hypot(particles[i]->getX() - x, particles[i]->getY() - y) <= particles[i]->getSize())
		{
			return particles[i];
		}
	}
	return nullptr;
}
//This creates a new SpringForce to the world, using a pointer to access the class and set the new forces
SpringForce* World::addSpring(Particles* particle1, Particles* particle2, float length, float strength)
{
	SpringForce* springForce = new SpringForce(particle1, particle2, length, strength);
	springForces.push_back(springForce);
	return springForce;
}
//This tells the world how the particle is supposed to bounce by getting the x and y values and setting the speed and angle to the right values
void World::bounce(Particles* particle)
{
	if (particle->getX() > (width - particle->getSize()))
	{
		particle->setX(2 * (width - particle->getSize()) - particle->getX());
		particle->setAngle(-particle->getAngle());
		particle->setSpeed(particle->getSpeed() * particle->getElasticity());
	}

	else if (particle->getX() < particle->getSize())
	{
		particle->setX(2 * particle->getSize() - particle->getX());
		particle->setAngle(-particle->getAngle());
		particle->setSpeed(particle->getSpeed() * particle->getElasticity());
	}

	if (particle->getY() > (height - particle->getSize()))
	{
		particle->setY(2 * (height - particle->getSize()) - particle->getY());
		particle->setAngle(M_PI - particle->getAngle());
		particle->setSpeed(particle->getSpeed() * particle->getElasticity());
	}

	else if (particle->getY() < particle->getSize())
	{
		particle->setY(2 * particle->getSize() - particle->getY());
		particle->setAngle(M_PI - particle->getAngle());
		particle->setSpeed(particle->getSpeed() * particle->getElasticity());
	}
}
//This erases the particles that may be found in a scene
void World::removeParticle(Particles* particle)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particle == particles[i])
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}
//This erases the spring that has been created in a scene
void World::removeSpring(SpringForce* springForce)
{
	for (int i = 0; i < springForces.size(); i++)
	{
		if (springForce == springForces[i])
		{
			delete springForces[i];
			springForces.erase(springForces.begin() + i);
		}
	}
}
//This updates the world overall
void World::update()
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particles* particle = particles[i];
		if (allowAccelerate)
		{
			particle->accelerate(acceleration);
		}

		if (allowMove)
		{
			particle->move();
		}

		if (allowDrag)
		{
			particle->experienceDrag();
		}

		if (allowBounce)
		{
			bounce(particle);
		}

		for (int x = i + 1; x < particles.size(); x++)
		{
			Particles* otherParticle = particles[x];

			if (allowCollide)
			{
				particle->collide(otherParticle);
			}

			if (allowAttract)
			{
				particle->attract(otherParticle);
			}

			if (allowCombine)
			{
				particle->combine(otherParticle);
			}
		}
	}

	for (int i = 0; i < springForces.size(); i++)
	{
		SpringForce* springForce = springForces[i];
		springForce->update();
	}
}