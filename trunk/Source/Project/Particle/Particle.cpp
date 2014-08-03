#include "Particle.hpp"

Particle& gParticle()
{
	static Particle sParticle;
	return sParticle;
}

