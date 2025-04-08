#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"

/*
	STL (Standard Template Library) : Vector
	�����迭�� �����ϴ� ǥ�� ���ø� ���̺귯�� �����̳�
	�迭�� ��������� ũ�Ⱑ �ڵ����� �����ȴ�.

	���� : �������� : �ε����� ����ؼ� O(1) �ð����⵵�� 
	���ҿ� ������ �����ϴ�.

	���� : �迭�� ����. �߰��� ���Ҹ� ����, ���� �� �� ����� 
	�ð����⵵ O(n) �� ���� ���.
*/

void Enemy::Init(float posX, float posY)
{
	pos = { posX, posY };
	moveSpeed = 0.01f;
	angle = -90.0f;
	isAlive = true;
	size = 30;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;

	image = ImageManager::GetInstance()->AddImage(
		"Normal_Enemy", TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
		true, RGB(255, 0, 255));

	//image = new Image();
	//image->Init(TEXT("Image/ufo.bmp"), 530, 32, 10, 1,
	//	true, RGB(255, 0, 255));

	missileManager = new MissileManager();
	missileManager->Init();

	missile = new Missile();
	missile->Init();
	missile->SetPos(pos);
	missile->SetAngle(-135);
	missile->SetIsActived(true);
}

void Enemy::Release()
{
	if (missile)
	{
		missile->Release();
		delete missile;
		missile = nullptr;
	}

	if (missileManager)
	{
		missileManager->Release();
		delete missileManager;
		missileManager = nullptr;
	}
}

void Enemy::Update()
{
	if (isAlive)
	{
		Move();
		//elapsedFrame++;

		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedTime > 0.1f)
		{
			animationFrame++;
			if (animationFrame >= image->GetMaxFrameX())
			{
				animationFrame = 0;
			}
			elapsedTime = 0.0f;
		}
	}

	if (missile)
		missile->Update();

}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
		//RenderRectAtCenter(hdc, pos.x, pos.y, size, size);
	}

	if (missile)
		missile->Render(hdc);
}

void Enemy::Move()
{
	if (target)
	{
		angle = GetAngle(pos, target->GetPos());

		pos.x += cosf(angle) * moveSpeed;
		pos.y -= sinf(angle) * moveSpeed;
	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
