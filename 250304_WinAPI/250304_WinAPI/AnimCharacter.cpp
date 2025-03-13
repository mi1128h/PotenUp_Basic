#include "AnimCharacter.h"
#include "Image.h"
#include "CommonFunction.h"

void AnimCharacter::Init()
{
	position = { 0,0 };
	speed = 10;

	for (int i = 0; i < State::Statelength; ++i) vImages[i] = {};

	Image* walkImages = new Image();
	if (FAILED(walkImages->Init(L"Image/iori_walk.bmp", 612, 104, 9, 1))) {
		MessageBox(g_hWnd, L"iori_walk 파일 로드에 실패", L"경고", MB_OK);
	}

	vImages[State::Walk].push_back(walkImages);
	curState = State::Walk;
	frameIdx = -1;
	flip = false;
}

void AnimCharacter::Release()
{
	for (auto images : vImages) {
		for (auto i : images) {
			i->Release();
			delete i;
			i = NULL;
		}
	}
}

void AnimCharacter::Update()
{
	Animate();
}

void AnimCharacter::Animate()
{
	frameIdx++;
	int size = vImages[curState].size();
	if (size > 0) {
		if (size != 1) {
			frameIdx %= size;
		}
		else if (size == 1) {
			int sn = vImages[curState][0]->GetSpritesNumX() * vImages[curState][0]->GetSpritesNumY();
			frameIdx %= sn;
		}
	}
	else frameIdx = -1;
}

void AnimCharacter::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int size = vImages[curState].size();
	if(size == 1)
		vImages[curState][0]->Render(hdc, position.x, position.y, frameIdx);
}

void AnimCharacter::Move(int dx, int dy)
{
	position.x += dx;
	position.y += dy;
	if (dx > 0) flip = false;
	if (dx < 0) flip = true;
}
