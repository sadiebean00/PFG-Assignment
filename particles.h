//This is the header class for the particles where the vector storing the angle and speed can be found
#pragma once
#ifndef PARTICLES_H
#define PARTICLES_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

struct Vector {
	float angle;
	float speed;
};

Vector operator+ (Vector const& vec1, Vector const& vec2);

class Particles {
public:
	Particles(float x, float y, float mass, float size, float speed, float angle, float elasticity, float drag);
	Particles* getCollideW() { return collideW; }

	float getAngle() { return angle; }
	float getDrag() { return drag; }
	float getElasticity() { return elasticity; }
	float getSpeed() { return speed; }
	float getMass() { return mass; }
	float getSize() { return size; }
	float getX() { return x; }
	float getY() { return y; }

	void accelerate(Vector vec);
	void attract(Particles* otherParticles);
	void collide(Particles* otherParticles);
	void combine(Particles* otherParticles);
	void experienceDrag();
	void move();
	void moveTo(float moveX, float moveY);
	void setAngle(float a) { angle = a; }
	void setDrag(float d) { drag = d; }
	void setMass(float m) { mass = m; }
	void setElasticity(float e) { elasticity = e; }
	void setSpeed(float sp) { speed = sp; }
	void setSize(float si) { size = si; }
	void setX(float xLoc) { x = xLoc; }
	void setY(float yLoc) { y = yLoc; }


protected:
	float angle;
	float drag;
	float mass;
	float speed;
	float size;
	float x;
	float y;
	float elasticity;

	Particles* collideW = NULL;
};

#endif // !PARTICLES_H
