#include "Bullet.h"
#include "CommonFunction.h"
#include "Enemy.h"
#include "Image.h"

void Bullet::Init(FPOINT pos, float angle, float dmg)
{
	isLoaded = true;
	position = pos;
	fireAngle = angle;
	speed = 200.0f;
	size = 10;
	damage = dmg;
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);

	guided = false;
	target = nullptr;

	ImageManager* im = ImageManager::GetInstance();
	im->LoadImageAtManager(L"Image/bullet.bmp", 21, 21, 1, 1, true, RGB(255, 0, 255));
	image = im->GetImage(L"Image/bullet.bmp");
}

void Bullet::SetValues(float explodeTime, float newAngle, int bounceNum, float confettiLife)
{
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	if (isLoaded) return;

	if (guided) {
		if (target) {
			UpdateGuidedAngle();
		}
	}

	Move();
	CheckWallCollision();
}

void Bullet::Render(HDC hdc)
{
	if (isLoaded) return;

	//RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
	if (image) {
		image->RenderCenter(hdc, position.x, position.y, 1, 1, 0, false);
	}
}

void Bullet::Move()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	position.x += cosf(TORADIAN(fireAngle)) * speed * deltaTime;
	position.y -= sinf(TORADIAN(fireAngle)) * speed * deltaTime;
}

void Bullet::UpdateGuidedAngle()
{
	if (!target) return;
	float targetAngle = GetAngle(position, target->GetPos());

	float dAngle = targetAngle - fireAngle;

	if (abs(dAngle) < 10) fireAngle = targetAngle;
	else {
		float angle{ dAngle };
		float min{ abs(dAngle) };
		if (min > abs(dAngle - 360)) {
			min = abs(dAngle - 360);
			angle = dAngle - 360;
		}
		if (min > abs(dAngle + 360)) {
			min = abs(dAngle + 360);
			angle = dAngle + 360;
		}
		fireAngle += angle * 0.3f;
	}
}

void Bullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) isLoaded = true;
}

void Bullet::CheckEnemyCollision(Enemy* enemy)
{
	if (isLoaded) return;
	if (enemy->IsDead()) return;

	if (CircleCollideCircle(position, enemy->GetPos(), size, enemy->GetSize())) {
		enemy->AttackedByBullet(damage);
		isLoaded = true;
	}
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

BombBullet::BombBullet()
{
}

BombBullet::~BombBullet()
{
}

void BombBullet::SetValues(float explodeTime, float newAngle, int bounceNum, float confettiLife)
{
	SetBombValues(explodeTime, newAngle);
}

void BombBullet::SetBombValues(float time, float angle)
{
	countDown = time;
	angle_360 = angle;
}

void BombBullet::Update()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	if (countDown > 0) countDown -= deltaTime;
	Bullet::Update();
}

void BombBullet::Move()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	if (countDown > 0) Bullet::Move();
	else {
		position.x += cosf(TORADIAN(angle_360)) * speed * deltaTime;
		position.y -= sinf(TORADIAN(angle_360)) * speed * deltaTime;
	}
}

BounceBullet::BounceBullet()
{
}

BounceBullet::~BounceBullet()
{
}

void BounceBullet::SetValues(float explodeTime, float newAngle, int bounceNum, float confettiLife)
{
	SetBounceValues(bounceNum);
}

void BounceBullet::SetBounceValues(int cnt)
{
	bounceNum = cnt;
}

void BounceBullet::CheckWallCollision()
{
	rcCollision = GetRectAtCenter(position.x, position.y, size, size);
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) {
		if (!bounceNum) isLoaded = true;
		else {
			bounceNum--;
			bool isUpsideDown = IsOutOfRange({ WINSIZE_X / 2, position.y }, WINSIZE_X, WINSIZE_Y);
			fireAngle = 180 * (isUpsideDown ? 2 : 1) - fireAngle;
			position.x = ClampVal(position.x, 10.0f, (float)WINSIZE_X - 10.0f);
			position.y = ClampVal(position.y, 10.0f, (float)WINSIZE_Y - 10.0f);
		}
	}
}

ConfettiBullet::ConfettiBullet()
{
}

ConfettiBullet::~ConfettiBullet()
{
}

void ConfettiBullet::SetValues(float explodeTime, float newAngle, int bounceNum, float confettiLife)
{
	BombBullet::SetBombValues(explodeTime, newAngle);
	SetConfettiValues(confettiLife);
}

void ConfettiBullet::SetConfettiValues(float life)
{
	//colors[0] = uid_200_255(dre);
	colors[0] = (float)uid_0_255(dre) / 255.0f * 55.0f + 200;
	colors[1] = uid_0_255(dre);
	colors[2] = uid_0_255(dre);
	//lifeTime = life * uid_1_2(dre);
	lifeTime = life * ((float)uid_0_255(dre) / 255.0f + 1.0f);
}

void ConfettiBullet::Update()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	BombBullet::Update();
	if (countDown <= 0) {
		//speed = uid_0_10(dre);
		speed = (float)uid_0_255(dre) / 255.0f * 300.0f;
		lifeTime -= deltaTime;
	}
	if (lifeTime <= 0) isLoaded = true;
}

void ConfettiBullet::Render(HDC hdc)
{
	if (isLoaded) return;
	if (countDown > 0) {
		Bullet::Render(hdc);
	}
	else {
		HBRUSH hBrush = CreateSolidBrush(RGB(colors[0], colors[1], colors[2]));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		RenderRectAtCenter(hdc, position.x, position.y, size * lifeTime, size * lifeTime);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
}
