#pragma once
#include "config.h"

class Image
{
public :
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// 프로젝트 자체에 포함 시킬 이미지
		File,		// 외부에서 로드할 이미지
		Empty,		// 자체 생산할 이미지
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유 ID
		HDC hMemDC;			// 그리기를 주관하는 객체 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입

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
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const wchar_t* filePath, int width, int height);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0);
	void Render(HDC hdc, int destX, int destY, int frameIndex);
	
	// 메모리 해제
	void Release();

	inline HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDC; else return NULL; }
};

