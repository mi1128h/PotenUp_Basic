#include "KOF_Iori.h"
#include "Image.h"

void KOF_Iori::Init()
{
	pos = { 0.0f, 0.0f };
	moveSpeed = 5.0f;
	image = new Image();
	if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1, 
		true, RGB(255,0,255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	elapsedFrame = 0;
	currAnimaionFrame = 0;
}

void KOF_Iori::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void KOF_Iori::Update()
{
	elapsedFrame++;
	//if (elapsedFrame >= 5)
	if (KeyManager::GetInstance()->IsOnceKeyUp(VK_SPACE))
	{
		currAnimaionFrame++;
		Move();

		if (currAnimaionFrame > 8)
		{
			currAnimaionFrame = 0;
		}
		elapsedFrame = 0;
	}
	//currAnimaionFrame = elapsedFrame / 5;
	//if (currAnimaionFrame > 8)
	//{
	//	currAnimaionFrame = 0;
	//	elapsedFrame = 0;
	//}
}

void KOF_Iori::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y, currAnimaionFrame, true);
}

void KOF_Iori::Move()
{
	pos.x += moveSpeed;
}

KOF_Iori::KOF_Iori()
{
}

KOF_Iori::~KOF_Iori()
{
}
