#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "CommonFunction.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;
	hp = 1000;
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
	confettiLife = 5;
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
	loadedNum = 0;
	for (auto b : vConfettis) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)SkillType::Confetti] = loadedNum;
}

void Tank::Render(HDC hdc)
{
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);

	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	for (auto b : vBullets) {
		b->Render(hdc);
	}

	RenderBulletsNum(hdc);
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
	case SkillType::Confetti:
		FireConfetti();
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

void Tank::FireConfetti()
{
	int fireSuccess{};

	if (nLoadedBullets[(int)SkillType::Confetti] > 0) {
		for (int i = 0; i < vConfettis.size(); ++i) {
			if (!vConfettis[i]->IsLoaded()) continue;
			vConfettis[i]->Init(barrelEnd, barrelAngle);
			vConfettis[i]->SetBombValues(bombExplodeTime, 6 * fireSuccess);
			vConfettis[i]->SetConfettiValues(confettiLife);
			vConfettis[i]->Fire();

			fireSuccess++;
			nLoadedBullets[(int)SkillType::Confetti]--;

			if (fireSuccess >= 60) break;
		}
	}

	while (fireSuccess < 60) {
		ConfettiBullet* bullet = new ConfettiBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(bombExplodeTime, 6 * fireSuccess);
		bullet->SetConfettiValues(confettiLife);
		bullet->Fire();
		vBullets.push_back(bullet);
		vConfettis.push_back(bullet);
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

void Tank::CheckCollideEnemy(Enemy* enemy)
{
	if (!enemy) return;

	if (CircleCollideCircle(pos, enemy->GetPos(), size, enemy->GetSize())) {
		enemy->AttackedByTank();
		hp -= enemy->GetDamage();
	}
	for (auto b : vBullets) {
		b->CheckEnemyCollision(enemy);
	}
}

int Tank::GetCreatedBulletsNum(SkillType type)
{
	switch (type) {
	case SkillType::Basic:
		return vBasics.size();
	case SkillType::Bomb:
		return vBombs.size();
	case SkillType::Bounce:
		return vBounces.size();
	case SkillType::Confetti:
		return vConfettis.size();
	}
	return -1;
}

void Tank::RenderBulletsNum(HDC hdc)
{
	TCHAR szText[128]{};
	wsprintf(szText, L"Basic Bullets Num: %d/%d",
		GetLoadedBulletsNum(SkillType::Basic), GetCreatedBulletsNum(SkillType::Basic));
	TextOut(hdc, 20, 180, szText, wcslen(szText));

	wsprintf(szText, L"Bomb Bullets Num: %d/%d",
		GetLoadedBulletsNum(SkillType::Bomb), GetCreatedBulletsNum(SkillType::Bomb));
	TextOut(hdc, 20, 200, szText, wcslen(szText));

	wsprintf(szText, L"Bounce Bullets Num: %d/%d",
		GetLoadedBulletsNum(SkillType::Bounce), GetCreatedBulletsNum(SkillType::Bounce));
	TextOut(hdc, 20, 220, szText, wcslen(szText));

	wsprintf(szText, L"Confetti Bullets Num: %d/%d",
		GetLoadedBulletsNum(SkillType::Confetti), GetCreatedBulletsNum(SkillType::Confetti));
	TextOut(hdc, 20, 240, szText, wcslen(szText));
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
