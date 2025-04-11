#pragma once
#include "Singleton.h"
#include "config.h"

///*
//	�迭 : �ε��� -> ������
//	stl::vector : �ε��� -> ������
//	std::map : Ű -> ������
//
//	����-�� Ʈ�� ���� : ����, ����, �˻� O(logN) �ð����⵵
//*/

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mapImages;

public:
	void Init();
	void Release();

	Image* AddImage(string key, const wchar_t* filePath,
		int width, int height,
		bool isTransparent = FALSE,
		COLORREF transColor = FALSE);

	Image* AddImage(string key, const wchar_t* filePath, 
		int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, 
		COLORREF transColor = FALSE);

	void DeleteImage(string key);
	Image* FindImage(string key);
};

