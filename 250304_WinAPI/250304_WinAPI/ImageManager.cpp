#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
}

void ImageManager::Release()
{
    for (pair<const wstring, Image*>& p : imageList) {
        if (p.second) {
            p.second->Release();
            delete p.second;
            p.second = NULL;
        }
    }
    imageList.clear();

    ReleaseInstance();
}

void ImageManager::LoadImageAtManager(const wchar_t* filePath, int width, int height, int spritesNumX, int spritesNumY, bool isTransparent, COLORREF transColor)
{
    wstring key(filePath);
    if (imageList[key]) return;

    imageList[key] = new Image;
    imageList[key]->Init(filePath, width, height, spritesNumX, spritesNumY, isTransparent, transColor);
}

Image* ImageManager::GetImage(wstring imageName)
{
    return imageList[imageName];
}
