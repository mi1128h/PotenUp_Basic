#include "Rocket.h"
#include "Image.h"
#include "CommonFunction.h"
#include "ImageManager.h"
#include "BulletManager.h"

void Rocket::Init()
{
	position = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	dx = 0;
	dy = 0;
	speed = 200;
	damage = 3;

	ImageManager* im = ImageManager::GetInstance();
	im->LoadImageAtManager(L"Image/rocket.bmp", 52, 64, 1, 1, true, RGB(255, 0, 255));
	image = im->GetImage(L"Image/rocket.bmp");

	bulletManager = new BulletManager;
	bulletManager->Init();
	bulletManager->SetBulletValues(90, damage, 1.5f, 5, 0.3f);
}

void Rocket::Release()
{
	if (bulletManager) {
		bulletManager->Release();
		delete bulletManager;
		bulletManager = NULL;
	}
}

void Rocket::Update()
{
	Move();

	Animate();

	ProcessInput();

	if (bulletManager)
		bulletManager->Update();
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

	if (km->IsOnceKeyDown(VK_SPACE)) {
		if (bulletManager) {
			bulletManager->Fire(BulletType::Basic, position);
		}
	}

	if(km->IsOnceKeyDown('I')) {
		if (bulletManager) {
			//bulletManager->Fire(BulletType::Bomb, position);
			//bulletManager->Fire(BulletType::Bounce, position);
			bulletManager->Fire(BulletType::Confetti, position);
		}
	}
}

void Rocket::Animate()
{
}

void Rocket::Render(HDC hdc)
{
	if (image)
		image->RenderCenter(hdc, position.x, position.y, 1, 1, 0, false);

	if (bulletManager)
		bulletManager->Render(hdc);
}

void Rocket::Move()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	position.x += dx * speed * deltaTime;
	position.y += dy * speed * deltaTime;

	int width{}, height{};
	if (image) {
		width = image->GetWidth() / image->GetSpritesNumX();
		height = image->GetHeight() / image->GetSpritesNumY();
	}
	
	position.x = ClampVal(position.x, 0.0f + width / 2, (float)WINSIZE_X - width / 2);
	position.y = ClampVal(position.y, 0.0f + height / 2, (float)WINSIZE_Y - height / 2);
}
