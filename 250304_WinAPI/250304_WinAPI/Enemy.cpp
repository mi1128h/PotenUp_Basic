#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Bullet.h"
#include "Image.h"

/*
	STL (Standard Template Library)
	Vector
	���� �迭�� �����ϴ� ǥ�� ���ø� ���̺귯�� �����̳�
	�迭�� ��������� ũ�Ⱑ �ڵ����� �����ȴ�

	����: ���� ����;�ε����� ����ؼ� O(1) �ð����⵵�� ���ҿ� ������ �����ϴ�
	����: �迭�� ����. �߰��� ���Ҹ� ����, ���� �� �� �ð����⵵ O(n)
*/


vector<Bullet*> Enemy::vBullets = {};
int Enemy::nLoadedBullets = 0;

void Enemy::Init(float x, float y, Tank* tank)
{
	position = { x, y };
	dx = 0;
	dy = 0;
	horizonMoveTime = 1.0f;
	target = tank;
	hp = 10;
	size = 20;
	speed = 100;
	damage = 10;
	bulletsNum = 0;
	fireInterval = 1;
	elapsedFireTime = 0;

	animationFrame = 0;
	elapsedTime = 0;
	
	rush = false;
	rushElapsedTime = 0;
	fireBullet = false;

	ImageManager* im = ImageManager::GetInstance();
	im->LoadImageAtManager(L"Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	image = im->GetImage(L"Image/ufo.bmp");
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
}

void Enemy::Update()
{
	if (hp <= 0) return;
	
	if (!rush) {
		HorizontalMove();
	}
	else {
		rushElapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		dx = 0;
		dy += 0.2f;
		dy = ClampVal(dy, 1.0f, 3.0f);
	}
	Move();

	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > 1) {
		animationFrame++;
		animationFrame %= image->GetSpritesNumX() * image->GetSpritesNumY();
		elapsedTime = 0.0f;
	}

	CheckWallCollision();
}

void Enemy::Render(HDC hdc)
{
	if (hp <= 0) return;

	image->RenderCenter(hdc, position.x, position.y, 1, 1, animationFrame, false);
	//RenderEllipseAtCenter(hdc, position.x, position.y, size, size);
}

void Enemy::HorizontalMove()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	if (horizonMoveTime > 0) {
		dx = 1;
		horizonMoveTime -= deltaTime;
	}
	else if (horizonMoveTime < 0) {
		dx = -1;
		horizonMoveTime += deltaTime;
	}

	if (abs(horizonMoveTime) <= 0.1) {
		horizonMoveTime = dx > 0 ? -1.0f : 1.0f;
	}
}

void Enemy::Move()
{
	//float moveAngle = 270;
	//if (target)
	//	moveAngle = GetAngle(position, target->GetPos());

	//position.x += cosf(TORADIAN(moveAngle)) * speed;
	//position.y -= sinf(TORADIAN(moveAngle)) * speed;

	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();

	position.x += dx * speed * deltaTime;
	position.y += dy * speed * deltaTime;
	int width{}, height{};
	if (image) {
		width = image->GetWidth() / image->GetSpritesNumX();
		height = image->GetHeight() / image->GetSpritesNumY();
	}
	position.x = ClampVal(position.x, 0.0f + width / 2, (float)WINSIZE_X - width / 2);
}

void Enemy::Fire()
{
	if (bulletsNum <= 0) return;
	float angle = GetAngle(position, target->GetPos());
	if (nLoadedBullets > 0) {
		for (int i = 0; i < vBullets.size(); ++i) {
			if (vBullets[i]->IsLoaded()) {
				vBullets[i]->Init(position, angle, damage);
				vBullets[i]->SetSpeed(bulletSpeed);
				vBullets[i]->Fire();
				nLoadedBullets--;
				break;
			}
		}
	}
	else {
		Bullet* bullet = new Bullet;
		bullet->Init(position, angle, damage);
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

void Enemy::CheckWallCollision()
{
	if (IsOutOfRange(position, WINSIZE_X, WINSIZE_Y)) hp = 0;
}