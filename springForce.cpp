//This handles the movement of the spring, as well as the forces controlling it.
#include "springForce.h"

SpringForce::SpringForce(Particles* particle1, Particles* particle2, float length, float strength) : particle1(particle1), particle2(particle2), length(length), strength(strength)
{

}
//This updates the spring force for both particle1 and particle2
void SpringForce::update()
{
	float dx = particle1->getX() - particle2->getX();
	float dy = particle1->getY() - particle2->getY();
	float dist = hypot(dx, dy);
	float theta = atan2(dy, dx);
	float force = (length - dist) * strength;

	particle1->accelerate(Vector{ static_cast<float>(theta + 0.5 * M_PI), force / particle1->getMass() });
	particle2->accelerate(Vector{ static_cast<float>(theta - 0.5 * M_PI), force / particle2->getMass() });
}