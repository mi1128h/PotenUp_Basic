#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
private:
	float life;
	POINT position;
	POINT direction;
	float colors[3];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	bool IsDead() { return !life; }
};

class ParticleSystem : public GameObject
{
private:
	vector<Particle*> vParticles;
	int nParticles;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

