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

	int skillNum = (int)SkillType::length;

	for (int i = 0; i < skillNum; ++i) {
		nLoadedBullets[i] = 0;
		skillsCooldownTime[i] = 0;
		skillsCooldownMaxTime[i] = 3 * (i + 1);
	}

	bombExplodeTime = 10;
	bounceNum = 5;
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

	for (auto b : vBullets) {
 		b->Update();
	}

	int loadedNum{};
	for (auto b : vBasics) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)SkillType::Basic] = loadedNum;
	loadedNum = 0;
	for (auto b : vBombs) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)SkillType::Bomb] = loadedNum;
	loadedNum = 0;
	for (auto b : vBounces) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)SkillType::Bounce] = loadedNum;
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
	if (type < SkillType::Basic) return;
	if (type >= SkillType::length) return;
	if (skillsCooldownTime[(int)type] > 0) return;
	skillsCooldownTime[(int)type] = skillsCooldownMaxTime[(int)type];

	switch (type) {
	case SkillType::Basic:
		Fire();
		break;
	case SkillType::Bomb:
		FireBomb();
		break;
	case SkillType::Bounce:
		FireBounce();
		break;
	}
}

void Tank::Fire()
{
	if (nLoadedBullets[(int)SkillType::Basic] > 0) {
		for (int i = 0; i < vBasics.size(); ++i) {
			if (vBasics[i]->IsLoaded()) {
				vBasics[i]->Init(barrelEnd, barrelAngle);
				vBasics[i]->Fire();
				nLoadedBullets[(int)SkillType::Basic]--;
				break;
			}
		}
	}
	else {
		Bullet* bullet = new Bullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBasics.push_back(bullet);
	}
}

void Tank::FireBomb()
{
	int fireSuccess{};

	if (nLoadedBullets[(int)SkillType::Bomb] > 0) {
		for (int i = 0; i < vBombs.size(); ++i) {
			if (!vBombs[i]->IsLoaded()) continue;
			vBombs[i]->Init(barrelEnd, barrelAngle);
			vBombs[i]->SetBombValues(bombExplodeTime, 10 * fireSuccess);
			vBombs[i]->Fire();

			fireSuccess++;
			nLoadedBullets[(int)SkillType::Bomb]--;

			if (fireSuccess >= 36) break;
		}
	}

	while(fireSuccess < 36 ) {
		BombBullet* bullet = new BombBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(bombExplodeTime, 10 * fireSuccess);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBombs.push_back(bullet);
		fireSuccess++;
	}
}

void Tank::FireBounce()
{
	if (nLoadedBullets[(int)SkillType::Bounce] > 0) {
		for (int i = 0; i < vBounces.size(); ++i) {
			if (vBounces[i]->IsLoaded()) {
				vBounces[i]->Init(barrelEnd, barrelAngle);
				vBounces[i]->SetBounceNum(bounceNum);
				vBounces[i]->Fire();
				nLoadedBullets[(int)SkillType::Bounce]--;
				break;
			}
		}
	}
	else {
		BounceBullet* bullet = new BounceBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBounceNum(bounceNum);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBounces.push_back(bullet);
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
