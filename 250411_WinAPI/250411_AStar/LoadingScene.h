#pragma once
#include "GameObject.h"

class Image;
class LoadingScene : public GameObject
{
public:
	virtual ~LoadingScene() {};

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

private:
	Image* bg;
};

