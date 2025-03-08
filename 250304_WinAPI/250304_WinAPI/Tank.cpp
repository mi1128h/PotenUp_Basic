#include "Tank.h"
#include "Bullet.h"
#include "CommonFunction.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;
	damage = 10;
	name = "≈ ≈©";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);

	barrelSize = 90;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 45;

	nLoadedBullets = 0;
	bombExplodeTime = 10;

	skillsCooldownTime[(int)SkillType::None] = 0;
	skillsCooldownTime[(int)SkillType::Bomb] = 0;
	skillsCooldownTime[(int)SkillType::Skill2] = 0;
}

void Tank::Release()
{
	for (int i = 0; i < vBullets.size(); ++i) {
		delete vBullets[i];
	}
}

void Tank::Update()
{
	barrelEnd.x = pos.x + barrelSize * cosf(TORADIAN(barrelAngle));
	barrelEnd.y = pos.y - barrelSize * sinf(TORADIAN(barrelAngle));

	for (int i = 0; i < (int)SkillType::length; ++i) {
		skillsCooldownTime[i]--;
	}

	int loadedBullets{};
	for (auto b : vBullets) {
 		b->Update();
		if (b->IsLoaded()) loadedBullets++;
	}
	nLoadedBullets = loadedBullets;
}

void Tank::Render(HDC hdc)
{
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);

	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	for (auto b : vBullets) {
		b->Render(hdc);
	}
}

void Tank::Move()
{
}

void Tank::Skill(SkillType type)
{
	if (type < SkillType::None) return;
	if (type >= SkillType::length) return;
	if (skillsCooldownTime[(int)type] > 0) return;
	skillsCooldownTime[(int)type] = skillsCooldownMaxTime[(int)type];

	switch (type) {
	case SkillType::None:
		Fire();
		break;
	case SkillType::Bomb:
		FireBomb();
		break;
	case SkillType::Skill2:

		break;
	}
}

void Tank::Fire()
{
	if (nLoadedBullets > 0) {
		for (int i = 0; i < vBullets.size(); ++i) {
			if (vBullets[i]->IsLoaded()) {
				vBullets[i]->Init(barrelEnd, barrelAngle);
				vBullets[i]->SetBombValues(0, barrelAngle);
				vBullets[i]->Fire();
				nLoadedBullets--;

				break;
			}
		}
	}
	else {
		BombBullet* bullet = new BombBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(0, barrelAngle);
		bullet->Fire();
		vBullets.push_back(bullet);
	}
}

void Tank::FireBomb()
{
	int fireSuccess{};

	if (nLoadedBullets > 0) {
		for (int i = 0; i < vBullets.size(); ++i) {
			if (!vBullets[i]->IsLoaded()) continue;
			vBullets[i]->Init(barrelEnd, barrelAngle);
			vBullets[i]->SetBombValues(bombExplodeTime, 10 * fireSuccess);
			vBullets[i]->Fire();

			fireSuccess++;
			nLoadedBullets--;

			if (fireSuccess >= 36) break;
		}
	}

	while(fireSuccess < 36 ) {
		BombBullet* bullet = new BombBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(bombExplodeTime, 10 * fireSuccess);
		bullet->Fire();
		vBullets.push_back(bullet);
		fireSuccess++;
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
}

void Tank::Dead()
{
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
