#include "Button.h"
#include "Image.h"

HRESULT Button::Init(int posX, int posY)
{
    state = ButtonState::NONE;
    image = ImageManager::GetInstance()->AddImage("¹öÆ°", L"Image/button.bmp", 122, 62, 1, 2);
    if (!image) return E_FAIL;

    pos.x = posX;
    pos.y = posY;

    rc.left = pos.x - image->GetFrameWidth() / 2;
    rc.top = pos.y - image->GetFrameHeight() / 2;
    rc.right = rc.left + image->GetFrameWidth();
    rc.bottom = rc.top + image->GetFrameHeight();


    return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{
    if (PtInRect(&rc, g_ptMouse))
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
        {
            state = ButtonState::DOWN;
        }
        else if (state == ButtonState::DOWN and
            KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
        {
            state = ButtonState::UP;

            if (buttonFunc) buttonFunc();
        }
    }
}

void Button::Render(HDC hdc)
{
    switch (state)
    {
    case ButtonState::NONE:
    case ButtonState::UP:
    {
        image->FrameRender(hdc, pos.x, pos.y, 0, 0);
        break;
    }
    case ButtonState::DOWN:
    {
        image->FrameRender(hdc, pos.x, pos.y, 0, 1);
        break;
    }
    }
}
