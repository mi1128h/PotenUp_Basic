#pragma once
#include "Singleton.h"
#include "config.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
public:
	void Init();
	void Release();

	void LoadImageAtManager(const wchar_t* filePath, int width, int height, int spritesNumX, int spritesNumY, bool isTransparent, COLORREF transColor);

	Image* GetImage(wstring imageName);

private:
	map<wstring, Image*> imageList;
};