#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);
	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;
	imageInfo->spritesNum[0] = 1;
	imageInfo->spritesNum[1] = 1;
	
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, int spritesNumX, int spritesNumY)
{
	HDC hdc = GetDC(g_hWnd);
	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_TYPE::File;
	imageInfo->spritesNum[0] = spritesNumX;
	imageInfo->spritesNum[1] = spritesNumY;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, bool flip)
{
	BitBlt(
		hdc,				// ���� ������ DC
		destX, destY,		// ���� ������ ��ġ
		imageInfo->width,	// �������� ����� ���� ũ��
		imageInfo->height,	// �������� ����� ���� ũ��
		imageInfo->hMemDC,	// ���� DC
		0, 0,				// ���� ���� ���� ��ġ
		SRCCOPY);			// ���� �ɼ�
}

void Image::Render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int frameIndex, bool flip)
{
	int x = frameIndex % imageInfo->spritesNum[0];
	int y = frameIndex / imageInfo->spritesNum[0];
	//BitBlt(
	//	hdc,
	//	destX, destY,
	//	imageInfo->width / imageInfo->spritesNum[0],
	//	imageInfo->height / imageInfo->spritesNum[1],
	//	imageInfo->hMemDC,
	//	imageInfo->width / imageInfo->spritesNum[0] * x, imageInfo->height / imageInfo->spritesNum[1] * y,
	//	SRCCOPY);

	int srcX{}, srcY{};
	int srcWidth{}, srcHeight{};
	srcX = imageInfo->width / imageInfo->spritesNum[0] * x;
	srcY = imageInfo->height / imageInfo->spritesNum[1] * y;
	srcWidth = imageInfo->width / imageInfo->spritesNum[0];
	srcHeight = imageInfo->height / imageInfo->spritesNum[1];
	if (flip) {
		srcX += srcWidth;
		srcWidth *= -1;
	}

	HDC hTempDC = CreateCompatibleDC(hdc);
	HBITMAP hTempBit = CreateCompatibleBitmap(hdc, destWidth, destHeight);
	HBITMAP hOldBit = (HBITMAP)SelectObject(hTempDC, hTempBit);
	
	StretchBlt(
		hTempDC,
		0, 0,
		destWidth, destHeight,
		imageInfo->hMemDC,
		srcX, srcY,
		srcWidth, srcHeight,
		SRCCOPY);

	TransparentBlt(
		hdc,
		destX, destY,
		destWidth, destHeight,
		hTempDC,
		0, 0,
		destWidth, destHeight,
		RGB(255,0,255));

	SelectObject(hTempDC, hOldBit);
	DeleteDC(hTempDC);
}

void Image::Release()
{
	if (imageInfo) {
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
		imageInfo = NULL;
	}
}
