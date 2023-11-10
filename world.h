//This is the header class for the world where the environment is created
#pragma once
#ifndef WORLD_H
#define WORLD_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include <random>
#include "particles.h"
#include "springForce.h"

class World {
public:
	World(int width, int height);
	~World();

	int getHeight() { return height; }
	int getWidth() { return width; }

	Particles* addParticle();
	Particles* addParticle(float x, float y, float size = 10, float mass = 100, float speed = 0, float angle = 0, float elasticity = 0.9);
	Particles* getParticle(float x, float y);

	SpringForce* addSpring(Particles* particle1, Particles* particle2, float length = 10000, float strength = 1000);

	std::vector<Particles* > getParticles() { return particles; }
	std::vector<SpringForce* > getSpringForce(){ return springForces; }

	void bounce(Particles* particle);
	void removeParticle(Particles* particle);
	void removeSpring(SpringForce* spring);

	void setAirMass(float a) { airM = a; }
	void setAllowAccelerate(bool setting) { allowAccelerate = setting; }
	void setAllowAttract(bool setting) { allowAttract = setting; }
	void setAllowBounce(bool setting) { allowBounce = setting; }
	void setAllowCollide(bool setting) { allowCollide = setting; }
	void setAllowCombine(bool setting) { allowCombine = setting; }
	void setAllowDrag(bool setting) { allowDrag = setting; }
	void setAllowMove(bool setting) { allowMove = setting; }
	void setElasticity(float e) { elasticity = e; }

	void update();

protected:
	const int height;
	const int width;

	bool allowAccelerate = true;
	bool allowAttract = false;
	bool allowBounce = true;
	bool allowCollide = true;
	bool allowCombine = false;
	bool allowDrag = true;
	bool allowMove = true;

	float airM = 0.2;
	float elasticity = 0.75;

	std::vector<Particles*> particles;
	std::vector<SpringForce*> springForces;
	Vector acceleration = { M_PI, 0.2 };
};

#endif // !WORLD_H
