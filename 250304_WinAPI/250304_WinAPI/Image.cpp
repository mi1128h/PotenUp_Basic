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
	
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height)
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

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY)
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

void Image::Render(HDC hdc, int destX, int destY, int frameIndex)
{
	BitBlt(
		hdc,
		destX, destY,
		imageInfo->width / 9,
		imageInfo->height,
		imageInfo->hMemDC,
		imageInfo->width / 9 * frameIndex, 0,
		SRCCOPY);
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
