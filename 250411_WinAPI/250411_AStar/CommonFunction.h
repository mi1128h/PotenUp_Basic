// CommonFunction.h
/*
	inline: �����Ϸ����� �Լ� ȣ���� ����ȭ �ϵ��� ��û�ϴ� Ű����
	�Ϲ����� �Լ����� �Լ� ȣ�� �ÿ� �Ű������� ���ø޸� ����, 
	�Լ� �����ּҸ� ȣ��, ��ȯ�ּҷ� �̵�
	// main.cpp
	int result = 3 + 6;

	inline int Add(int a, int b)
	{
		return a + b;
	}
*/
#pragma once
#include "config.h"

inline RECT GetRect(int left, int top, int width, int height)
{
	RECT rc{ left, top, left + width, top + height };
	return rc;
}

inline RECT GetRectAtCenter(int x, int y, int width, int height)
{
	RECT rc{ x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}

inline void RenderStar(HDC hdc, int posX, int posY)
{
	MoveToEx(hdc, posX + 60, posY + 20, NULL);
	LineTo(hdc, posX - 60, posY + 20);
	LineTo(hdc, posX + 40, posY - 60);
	LineTo(hdc, posX, posY + 60);
	LineTo(hdc, posX - 40, posY - 60);
	LineTo(hdc, posX + 60, posY + 20);
}

// �»�� ����
inline void RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// ��� ����
inline void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

// �»�� ����
inline void RenderEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// ��� ����
inline void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

inline bool PointInRect(POINT ptMouse, RECT rc)
{
	if (ptMouse.x < rc.left || ptMouse.x > rc.right
		|| ptMouse.y < rc.top || ptMouse.y > rc.bottom)
	{
		return false;
	}
	return true;
}

inline bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left || rc1.left > rc2.right
		|| rc1.top > rc2.bottom || rc1.bottom < rc2.top)
	{
		return false;
	}
	return true;
}

inline void UpdateRect(RECT& rc, FPOINT pt)
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rc.left = pt.x - (width / 2);
	rc.right = rc.left + width;
	rc.top = pt.y - (height / 2);
	rc.bottom = rc.top + height;
}

inline float GetAngle(FPOINT start, FPOINT end)
{
	float x = end.x - start.x;
	float y = end.y - start.y;

	 return -atan2f(y, x);	// ����
}

inline float GetDistance(FPOINT p1, FPOINT p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;

	 return sqrtf(x * x + y * y);
}

inline FPOINT RotatePoint(const FPOINT& p, double angleRad) {
	FPOINT rotated;
	rotated.x = p.x * std::cos(angleRad) - p.y * std::sin(angleRad);
	rotated.y = p.x * std::sin(angleRad) + p.y * std::cos(angleRad);
	return rotated;
}

inline void SetClientRect(HWND hWnd, int width, int height)
{
	RECT rc;
	DWORD style = GetWindowLong(hWnd, GWL_STYLE);
	DWORD exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);

	SetRect(&rc, 0, 0, width, height);
	AdjustWindowRectEx(&rc, style, GetMenu(hWnd) != NULL, exStyle);
	if (style & WS_VSCROLL)
		rc.right += GetSystemMetrics(SM_CXVSCROLL);
	if (style & WS_HSCROLL)
		rc.bottom += GetSystemMetrics(SM_CYHSCROLL);

	SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, 
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
}