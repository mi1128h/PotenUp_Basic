#include "Rocket.h"
#include "Image.h"
#include "CommonFunction.h"

void Rocket::Init()
{
	position = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	dx = 0;
	dy = 0;
	speed = 10;

	image = new Image();
	image->Init(L"Image/rocket.bmp", 52, 64, 1, 1, true, RGB(255, 0, 255));
}

void Rocket::Release()
{
	if (image) {
		image->Release();
		delete image;
		image = NULL;
	}
}

void Rocket::Update()
{
	Move();

	Animate();

	ProcessInput();
}

void Rocket::ProcessInput()
{
	KeyManager* km = KeyManager::GetInstance();
	int deltaX{}, deltaY{};
	if (km->IsOnceKeyDown('A')) {
		deltaX -= 1;
	}
	if (km->IsOnceKeyDown('D')) {
		deltaX += 1;
	}
	if (km->IsOnceKeyDown('W')) {
		deltaY -= 1;
	}
	if (km->IsOnceKeyDown('S')) {
		deltaY += 1;
	}
	dx = deltaX;
	dy = deltaY;
}

void Rocket::Animate()
{
}

void Rocket::Render(HDC hdc)
{
	if (!image) return;
	image->RenderCenter(hdc, position.x, position.y, 1, 1, 0, false);
}

void Rocket::Move()
{
	position.x += dx * speed;
	position.y += dy * speed;

	int width{}, height{};
	if (image) {
		width = image->GetWidth();
		height = image->GetHeight();
	}
	
	position.x = ClampVal(position.x, 0.0f + width / 2, (float)WINSIZE_X - width / 2);
	position.y = ClampVal(position.y, 0.0f + height / 2, (float)WINSIZE_Y - height / 2);
}
