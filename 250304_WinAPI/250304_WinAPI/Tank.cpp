#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "CommonFunction.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;
	hp = 100;
	damage = 10;
	name = "≈ ≈©";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);

	barrelSize = 90;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 90;

	int skillNum = (int)BulletType::length;

	for (int i = 0; i < skillNum; ++i) {
		nLoadedBullets[i] = 0;
		skillsCooldownTime[i] = 0;
		skillsCooldownMaxTime[i] = 3 * (i + 1);
	}

	bombExplodeTime = 10;
	bounceNum = 5;
	confettiLife = 5;

	guidedFired = 1;

	for (auto b : vBullets)
	{
		b->SetLoaded(true);
	}

}

void Tank::Release()
{
	for (int i = 0; i < vBullets.size(); ++i) {
		delete vBullets[i];
	}
}

void Tank::Update()
{
	CalcBarrelEnd();

	for (int i = 0; i < (int)BulletType::length; ++i) {
		skillsCooldownTime[i]--;
	}

	for (auto b : vBullets) {
		b->Update();
	}

	int loadedNum{};
	for (auto b : vBasics) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)BulletType::Basic] = loadedNum;
	loadedNum = 0;
	for (auto b : vBombs) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)BulletType::Bomb] = loadedNum;
	loadedNum = 0;
	for (auto b : vBounces) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)BulletType::Bounce] = loadedNum;
	loadedNum = 0;
	for (auto b : vConfettis) {
		if (b->IsLoaded()) loadedNum++;
	}
	nLoadedBullets[(int)BulletType::Confetti] = loadedNum;
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

void Tank::Move(int dx, int dy)
{
	pos.x += dx;
	pos.y += dy;
	pos.x = ClampVal(pos.x, 0.0f, (float)WINSIZE_X);
	pos.y = ClampVal(pos.y, 0.0f, (float)WINSIZE_Y);
}

void Tank::Skill(BulletType type)
{
	if (type < BulletType::Basic) return;
	if (type >= BulletType::length) return;
	if (skillsCooldownTime[(int)type] > 0) return;
	skillsCooldownTime[(int)type] = skillsCooldownMaxTime[(int)type];

	switch (type) {
	case BulletType::Basic:
		Fire();
		break;
	case BulletType::Bomb:
		FireBomb();
		break;
	case BulletType::Bounce:
		FireBounce();
		break;
	case BulletType::Confetti:
		FireConfetti();
		break;
	}
}

void Tank::Fire()
{
	if (nLoadedBullets[(int)BulletType::Basic] > 0) {
		for (int i = 0; i < vBasics.size(); ++i) {
			if (vBasics[i]->IsLoaded()) {
				vBasics[i]->Init(barrelEnd, barrelAngle);
				if (!guidedFired) {
					vBasics[i]->SetGuided(true);
				}
				vBasics[i]->SetDamage(damage);
				vBasics[i]->Fire();
				nLoadedBullets[(int)BulletType::Basic]--;
				break;
			}
		}
	}
	else {
		Bullet* bullet = new Bullet;
		bullet->Init(barrelEnd, barrelAngle);
		if (!guidedFired) {
			bullet->SetGuided(true);
		}
		bullet->SetDamage(damage);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBasics.push_back(bullet);
	}
	IncreaseFiredCnt();
}

void Tank::FireBomb()
{
	int fireSuccess{};

	if (nLoadedBullets[(int)BulletType::Bomb] > 0) {
		for (int i = 0; i < vBombs.size(); ++i) {
			if (!vBombs[i]->IsLoaded()) continue;
			vBombs[i]->Init(barrelEnd, barrelAngle);
			vBombs[i]->SetBombValues(bombExplodeTime, 10 * fireSuccess);
			vBombs[i]->SetDamage(damage);
			vBombs[i]->Fire();

			fireSuccess++;
			nLoadedBullets[(int)BulletType::Bomb]--;

			if (fireSuccess >= 36) break;
		}
	}

	while (fireSuccess < 36) {
		BombBullet* bullet = new BombBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(bombExplodeTime, 10 * fireSuccess);
		bullet->SetDamage(damage);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBombs.push_back(bullet);
		fireSuccess++;
	}
}

void Tank::FireBounce()
{
	if (nLoadedBullets[(int)BulletType::Bounce] > 0) {
		for (int i = 0; i < vBounces.size(); ++i) {
			if (vBounces[i]->IsLoaded()) {
				vBounces[i]->Init(barrelEnd, barrelAngle);
				vBounces[i]->SetBounceNum(bounceNum);
				vBounces[i]->SetDamage(damage);
				vBounces[i]->Fire();
				nLoadedBullets[(int)BulletType::Bounce]--;
				break;
			}
		}
	}
	else {
		BounceBullet* bullet = new BounceBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBounceNum(bounceNum);
		bullet->SetDamage(damage);
		bullet->Fire();
		vBullets.push_back(bullet);
		vBounces.push_back(bullet);
	}
}

void Tank::FireConfetti()
{
	int fireSuccess{};

	if (nLoadedBullets[(int)BulletType::Confetti] > 0) {
		for (int i = 0; i < vConfettis.size(); ++i) {
			if (!vConfettis[i]->IsLoaded()) continue;
			vConfettis[i]->Init(barrelEnd, barrelAngle);
			vConfettis[i]->SetBombValues(bombExplodeTime, 6 * fireSuccess);
			vConfettis[i]->SetConfettiValues(confettiLife);
			vConfettis[i]->SetDamage(damage);
			vConfettis[i]->Fire();

			fireSuccess++;
			nLoadedBullets[(int)BulletType::Confetti]--;

			if (fireSuccess >= 60) break;
		}
	}

	while (fireSuccess < 60) {
		ConfettiBullet* bullet = new ConfettiBullet;
		bullet->Init(barrelEnd, barrelAngle);
		bullet->SetBombValues(bombExplodeTime, 6 * fireSuccess);
		bullet->SetConfettiValues(confettiLife);
		bullet->SetDamage(damage);
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

void Tank::CalcBarrelEnd()
{
	barrelEnd.x = pos.x + barrelSize * cosf(TORADIAN(barrelAngle));
	barrelEnd.y = pos.y - barrelSize * sinf(TORADIAN(barrelAngle));
}

void Tank::Dead()
{
}

void Tank::ProccessMoveInput(WPARAM wParam)
{
	switch (wParam) {
	case VK_LEFT:
		Move(-10, 0);
		break;
	case VK_RIGHT:
		Move(10, 0);
		break;
	case VK_UP:
		Move(0, -10);
		break;
	case VK_DOWN:
		Move(0, 10);
		break;
	}


	CalcBarrelEnd();
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

void Tank::SetBulletsTarget(vector<Enemy*>& enemies)
{
	for (auto b : vBullets) {
		if (b->IsLoaded()) continue;
		if (!b->IsGuided()) continue;

		Enemy* e = b->GetTarget();
		if (e) {
			if (e->IsDead())
				b->SetTarget(nullptr);
		}

		if (!b->GetTarget()) {
			Enemy* enemy = GetNearestEnemy(b->GetPos(), enemies);
			if (enemy) b->SetTarget(enemy);
		}
	}
}

Enemy* Tank::GetNearestEnemy(FPOINT pos, vector<Enemy*>& enemies)
{
	float minDist = INT_MAX;
	Enemy* target = nullptr;

	for (auto e : enemies) {
		if (e->IsDead()) continue;
		float dist = GetDistance(pos, e->GetPos());
		if (dist < minDist) {
			minDist = dist;
			target = e;
		}
	}

	return target;
}

int Tank::GetCreatedBulletsNum(BulletType type)
{
	switch (type) {
	case BulletType::Basic:
		return vBasics.size();
	case BulletType::Bomb:
		return vBombs.size();
	case BulletType::Bounce:
		return vBounces.size();
	case BulletType::Confetti:
		return vConfettis.size();
	}
	return -1;
}

void Tank::RenderInfo(HDC hdc)
{
	TCHAR szText[128]{};
	wsprintf(szText, L"Basic Bullets Num: %d/%d",
		GetLoadedBulletsNum(BulletType::Basic), GetCreatedBulletsNum(BulletType::Basic));
	TextOut(hdc, 20, 180, szText, wcslen(szText));

	wsprintf(szText, L"Bomb Bullets Num: %d/%d",
		GetLoadedBulletsNum(BulletType::Bomb), GetCreatedBulletsNum(BulletType::Bomb));
	TextOut(hdc, 20, 200, szText, wcslen(szText));

	wsprintf(szText, L"Bounce Bullets Num: %d/%d",
		GetLoadedBulletsNum(BulletType::Bounce), GetCreatedBulletsNum(BulletType::Bounce));
	TextOut(hdc, 20, 220, szText, wcslen(szText));

	wsprintf(szText, L"Confetti Bullets Num: %d/%d",
		GetLoadedBulletsNum(BulletType::Confetti), GetCreatedBulletsNum(BulletType::Confetti));
	TextOut(hdc, 20, 240, szText, wcslen(szText));

	wsprintf(szText, L"Tank Hp: %d", hp);
	TextOut(hdc, 20, 260, szText, wcslen(szText));
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
