#pragma once
#include "GameObject.h"

enum State {
	Idle,
	Walk,
	Dead,
	Statelength
};

class Image;
class AnimCharacter : public GameObject
{
private:
	FPOINT position;
	float speed;

	vector<Image*> vImages[State::Statelength];
	State curState;
	int frameIdx;
	bool flip;

public:
	void Init();
	void Release();
	void Update();
	void Animate();
	void Render(HDC hdc);

	void Move(int dx, int dy);

	FPOINT GetPos() { return position; }
	State GetState() { return curState; }
	void SetState(State state) { curState = state; }
};

