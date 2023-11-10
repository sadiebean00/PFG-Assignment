//Handles the forces and movement of the spring for the particle.
#pragma once
#ifndef SPRING_FORCE_H
#define SPRING_FORCE_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include "particles.h"

class SpringForce {
public:
	SpringForce(Particles* particle1, Particles* particle2, float length = 50, float strength = 0.5);
	Particles* getParticle1() { return particle1; }
	Particles* getParticle2() { return particle2; }

	void update();

protected:
	float length;
	float strength;
	Particles* particle1;
	Particles* particle2;
};

#endif // !SPRING_FORCE_H
