#pragma once
#include "config.h"

class Image
{
public :
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// ������Ʈ ��ü�� ���� ��ų �̹���
		File,		// �ܺο��� �ε��� �̹���
		Empty,		// ��ü ������ �̹���
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ���� ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� ��ü �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::Empty;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// LPIMAGE_INFO imageInfo

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const wchar_t* filePath, int width, int height);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0);
	void Render(HDC hdc, int destX, int destY, int frameIndex);
	
	// �޸� ����
	void Release();

	inline HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDC; else return NULL; }
};

