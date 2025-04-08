#include "Tank.h"
#include "CommonFunction.h"
#include "Missile.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 100;
	damage = 10;
	name = "��ũ";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);

	// ����
	barrelSize = 90;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 45.0f;

	// �̻���
	missileCount = 10;
	missiles = new Missile[missileCount];
	for (int i = 0; i < missileCount; i++)
	{
		//(*). ->
		missiles[i].Init();
	}

}

void Tank::Release()
{
	if (missiles)
	{
		for (int i = 0; i < missileCount; i++)
		{
			missiles[i].Release();
		}
		delete [] missiles;
	}
}

void Tank::Update()
{
	barrelEnd.x = pos.x + barrelSize * cosf(DEG_TO_RAD(barrelAngle));
	barrelEnd.y = pos.y - barrelSize * sinf(DEG_TO_RAD(barrelAngle));

	if (missiles)
	{
		for (int i = 0; i < missileCount; i++)
		{
			missiles[i].Update();
		}
	}
}

void Tank::Render(HDC hdc)
{
	// ����
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	if (missiles)
	{
		for (int i = 0; i < missileCount; i++)
		{
			missiles[i].Render(hdc);
		}
	}
}

void Tank::Move()
{
}

void Tank::Fire()
{
	if (missiles)
	{
		for (int i = 0; i < missileCount; i++)
		{
			if (missiles[i].GetIsActived() == false)
			{
				missiles[i].SetIsActived(true);
				missiles[i].SetPos(barrelEnd);
				missiles[i].SetAngle(barrelAngle);
				break;
			}
		}
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
