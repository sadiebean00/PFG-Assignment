//This handles the movements of the particles on the screen

#include "particles.h"
//This is the operator which adds the two vectors together
Vector operator+(Vector const& vec1, Vector const& vec2)
{
	float x = sin(vec1.angle) * vec1.speed + sin(vec2.angle) * vec2.speed;
	float y = cos(vec1.angle) * vec1.speed + cos(vec2.angle) * vec2.speed;
	return Vector{ static_cast<float>(0.5 * M_PI - atan2(y, x)), hypot(x, y) };
}
//This constructs the particle
Particles::Particles(float x, float y, float size, float mass, float speed, float angle, float elasticity, float drag) : 
	x(x), y(y), size(size), mass(mass), speed(speed), angle(angle), elasticity(elasticity), drag(drag)
{
	
}
//This accelerates the particles
void Particles::accelerate(Vector vec)
{
	Vector vel = Vector{ angle, speed } + vec;
	angle = vel.angle;
	speed = vel.speed;
}
//This attracts the particles to one another
void Particles::attract(Particles* otherParticle)
{
	float dx = x - otherParticle->x;
	float dy = y - otherParticle->y;
	float dist = hypot(dx, dy);
	float theta = atan2(dy, dx);
	float force = 0.2 * mass * otherParticle->mass / pow(dist, 2);

	accelerate(Vector{ static_cast<float>(theta - 0.5 * M_PI), force / mass });
	otherParticle->accelerate(Vector{ static_cast<float>(theta + 0.5 * M_PI), force / otherParticle->mass });
}
//This is how the particles collide with one another, detecting the size of the other particle
void Particles::collide(Particles* otherParticle)
{
	float dx = x - otherParticle->x;
	float dy = y - otherParticle->y;
	float dist = hypot(dx, dy);
	
	if (dist < (size + otherParticle->size))
	{
		float tang = atan2(dy, dx);
		float angleNew = 0.5f * M_PI + tang;
		float massTot = mass + otherParticle->mass;

		Vector vec1 = Vector{ angle, speed * (mass - otherParticle->mass) / massTot } + Vector{ angleNew, 2 * otherParticle->speed * otherParticle->mass / massTot };
		Vector vec2 = Vector{ otherParticle->angle, otherParticle->speed * (otherParticle->mass - mass) / massTot } + Vector{ static_cast<float>(angleNew + M_PI), 2 * speed * mass / massTot };

		angle = vec1.angle;
		speed = vec1.speed;
		otherParticle->angle = vec2.angle;
		otherParticle->speed = vec2.speed;

		float elasticityNew = elasticity * otherParticle->elasticity;
		speed *= elasticityNew;
		otherParticle->speed = elasticityNew;

		float overlap = 0.5f * (size + otherParticle->size - dist + 1);
		x += sin(angleNew) * overlap;
		y += cos(angleNew) * overlap;
		otherParticle->x -= sin(angleNew) * overlap;
		otherParticle->y -= cos(angleNew) * overlap;
	}
}
//This is used to combine two particles together.
void Particles::combine(Particles* otherParticle)
{
	float dx = x - otherParticle->x;
	float dy = y - otherParticle->y;
	float dist = hypot(dx, dy);

	if (dist < (size + otherParticle->size))
	{
		float massTot = mass + otherParticle->mass;
		x = (x * mass + otherParticle->x * otherParticle->mass) / massTot;
		y = (y * mass + otherParticle->y * otherParticle->mass) / massTot;

		Vector vec = Vector{ angle, speed * mass / massTot } + Vector{ otherParticle->angle, otherParticle->speed * otherParticle->mass / massTot };

		angle = vec.angle;
		speed = vec.speed * (elasticity * otherParticle->elasticity);

		mass += otherParticle->mass;
		collideW = otherParticle;
	}
}
//This tells the particles whether the speed needs to be affected with a drag
void Particles::experienceDrag()
{
	speed *= drag;
}
//This moves the particle and then updates the position of said particle
void Particles::move()
{
	x += sin(angle) * speed;
	y -= cos(angle) * speed;
}
//This moves the particle to a set location, found at x and y
void Particles::moveTo(float moveX, float moveY)
{
	float dx = moveX - x;
	float dy = moveY - y;
	angle = atan2(dy, dx) + 0.5 * M_PI;
	speed = hypot(dx, dy) * 0.1;
}