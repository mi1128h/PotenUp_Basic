#include "AnimBackground.h"
#include "Image.h"

void AnimBackground::Init()
{
	position = { 0,0 };
	speed = 10;

	for (int i = 0; i < Stage::Stagelength; ++i) vImages[i] = {};

	ImageManager* im = ImageManager::GetInstance();
	im->LoadImageAtManager(L"Image/background.bmp", 600, 800, 1, 1, FALSE, FALSE);
	Image* background = im->GetImage(L"Image/background.bmp");

	vImages[Stage::Stage1].push_back(background);
	curStage = Stage::Stage1;
	frameIdx = -1;
}

void AnimBackground::Release()
{
}

void AnimBackground::Update()
{
	Animate();
}

void AnimBackground::Animate()
{
	frameIdx++;
	int size = vImages[curStage].size();
	if (size > 0) {
		if (size != 1) {
			frameIdx %= size;
		}
		else if (size == 1) {
			int sn = vImages[curStage][0]->GetSpritesNumX() * vImages[curStage][0]->GetSpritesNumY();
			frameIdx %= sn;
		}
	}
	else frameIdx = -1;
}

void AnimBackground::Render(HDC hdc)
{
	if (frameIdx == -1) return;
	int size = vImages[curStage].size();
	if (size == 1)
		vImages[curStage][0]->Render(hdc, position.x, position.y, WINSIZE_X, WINSIZE_Y, frameIdx);
}
