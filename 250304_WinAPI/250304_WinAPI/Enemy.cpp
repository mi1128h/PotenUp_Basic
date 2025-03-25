#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Bullet.h"
#include "Image.h"

/*
	STL (Standard Template Library)
	Vector
	동적 배열을 제공하는 표준 템플릿 라이브러리 컨테이너
	배열과 흡사하지만 크기가 자동으로 조절된다

	장점: 임의 접근;인덱스를 사용해서 O(1) 시간복잡도로 원소에 접근이 가능하다
	단점: 배열과 같다. 중간에 원소를 삽입, 삭제 할 때 시간복잡도 O(n)
*/


vector<Bullet*> Enemy::vBullets = {};
int Enemy::nLoadedBullets = 0;

void Enemy::Init(Tank* tank)
{
	position.x = uid_0_WINSIZEX(dre);
	position.y = 50;
	target = tank;
	hp = 10;
	size = 20;
	speed = 10;
	damage = 10;
	bulletsNum = 0;
	fireInterval = 1;
	elapsedFireTime = 0;

	animationFrame = 0;
	elapsedFrame = 0;
	image = new Image();
	image->Init(L"Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
}

void Enemy::SetValuesByRound(float hp, int maxBulletNum, float speed, float size, int fireSpeed, float bulletSpeed)
{
	this->hp = hp;
	this->bulletsNum = maxBulletNum;
	this->speed = speed;
	this->size = size;
	this->fireInterval = fireSpeed;
	this->elapsedFireTime = fireSpeed / 2;
	this->bulletSpeed = bulletSpeed;
}

void Enemy::Release()
{
	if (image) {
		image->Release();
		delete image;
		image = NULL;
	}
}

void Enemy::Update()
{
	if (hp <= 0) return;

	Move();
	elapsedFireTime++;
	elapsedFireTime %= fireInterval;
	if (elapsedFireTime == 0) {
		Fire();
	}

	elapsedFrame++;
	if (elapsedFrame > 1) {
		animationFrame++;
		elapsedFrame = 0;
		animationFrame %= image->GetSpritesNumX() * image->GetSpritesNumY();
	}
}

void Enemy::Render(HDC hdc)
{
	if (hp <= 0) return;
	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	//RenderEllipseAtCenter(hdc, position.x, position.y, size, size);

	//SelectObject(hdc, hOldBrush);
	//DeleteObject(hBrush);

	//image->Render(hdc, position.x, position.y,
	//	image->GetWidth() / image->GetSpritesNumX(), image->GetHeight() / image->GetSpritesNumY(),
	//	animationFrame, false);
	image->RenderCenter(hdc, position.x, position.y, 1, 1, animationFrame, false);
	RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
}

void Enemy::Move()
{
	float moveAngle = 270;
	if (target)
		moveAngle = GetAngle(position, target->GetPos());

	//position.x += cosf(TORADIAN(moveAngle)) * speed;
	//position.y -= sinf(TORADIAN(moveAngle)) * speed;
}

void Enemy::Fire()
{
	if (bulletsNum <= 0) return;
	float angle = GetAngle(position, target->GetPos());
	if (nLoadedBullets > 0) {
		for (int i = 0; i < vBullets.size(); ++i) {
			if (vBullets[i]->IsLoaded()) {
				vBullets[i]->Init(position, angle);
				vBullets[i]->SetSpeed(bulletSpeed);
				vBullets[i]->Fire();
				nLoadedBullets--;
				break;
			}
		}
	}
	else {
		Bullet* bullet = new Bullet;
		bullet->Init(position, angle);
		bullet->SetSpeed(bulletSpeed);
		bullet->Fire();
		vBullets.push_back(bullet);
	}

	bulletsNum--;
}

void Enemy::ReleaseBullets()
{
	for (auto b : vBullets)
		if (b) delete b;
}

void Enemy::UpdateBullets()
{
	for (auto b : vBullets) {
		b->Update();
	}
}

void Enemy::RenderBullets(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	for (auto b : vBullets) {
		b->Render(hdc);
	}

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void Enemy::CheckBulletsCollision(Tank* tank)
{
	for (auto b : vBullets) {
		if (b->IsLoaded()) continue;
		bool collide = CircleCollideCircle(b->GetPos(), tank->GetPos(), b->GetSize(), tank->GetSize());
		if (collide) {
			b->SetLoaded(true);
			tank->AttackedByBullet(b->GetDamage());
		}
	}
}

void Enemy::InitLoadedBullets()
{
	for (auto b : vBullets)
	{
		b->SetLoaded(true);
	}
}
