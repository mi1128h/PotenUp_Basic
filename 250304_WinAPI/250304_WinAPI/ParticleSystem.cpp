#include "ParticleSystem.h"

void Particle::Init()
{
	life = 20;
	position = { 0,0 };
	direction = { uid(dre), uid(dre) };
}

void Particle::Update()
{
	if (life <= 0) return;
	life--;

}

void Particle::Render(HDC hdc)
{
}

void Particle::Release()
{
}

void ParticleSystem::Init()
{
}

void ParticleSystem::Update()
{
}

void ParticleSystem::Render(HDC hdc)
{
}

void ParticleSystem::Release()
{
}
