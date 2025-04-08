#include "TilemapTool.h"
#include "Image.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Button.h"

TilemapTool::TilemapTool()
{
}

TilemapTool::~TilemapTool()
{
}

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOL_X, TILEMAPTOOL_Y);

    sampleTile = ImageManager::GetInstance()->AddImage(
        "배틀시티_샘플타일", L"Image\\maptiles.bmp", 640, 288, SAMPLE_TILE_X, SAMPLE_TILE_Y);

    rcSampleTile.left = TILEMAPTOOL_X - sampleTile->GetWidth();
    rcSampleTile.top = 0;
    rcSampleTile.right = TILEMAPTOOL_X;
    rcSampleTile.bottom = sampleTile->GetHeight();

    selectedTile = { 3,0 };

    for (int i = 0; i < TILE_Y; ++i)
    {
        for (int j = 0; j < TILE_X; ++j)
        {
            tileInfo[i * TILE_X + j].frameX = selectedTile.x;
            tileInfo[i * TILE_X + j].frameY = selectedTile.y;
            tileInfo[i * TILE_X + j].rc.left = j * TILE_SIZE;
            tileInfo[i * TILE_X + j].rc.top = i * TILE_SIZE;
            tileInfo[i * TILE_X + j].rc.right = tileInfo[i * TILE_X + j].rc.left + TILE_SIZE;
            tileInfo[i * TILE_X + j].rc.bottom = tileInfo[i * TILE_X + j].rc.top + TILE_SIZE;
        }
    }

    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = TILE_X * TILE_SIZE;
    rcMain.bottom = TILE_Y * TILE_SIZE;

    // UI
    saveButton = new Button();
    saveButton->Init(TILEMAPTOOL_X - sampleTile->GetWidth() + 180, sampleTile->GetHeight() + 100);
    saveButton->SetFunction(std::bind(&TilemapTool::SaveTilemap, this));

    loadButton = new Button();
    loadButton->Init(TILEMAPTOOL_X - sampleTile->GetWidth() + 310, sampleTile->GetHeight() + 100);
    loadButton->SetFunction(std::bind(&TilemapTool::LoadTilemap, this));

    return S_OK;
}

void TilemapTool::Release()
{
    if (saveButton)
    {
        saveButton->Release();
        delete saveButton;
        saveButton = nullptr;
    }
    if (loadButton)
    {
        loadButton->Release();
        delete loadButton;
        loadButton = nullptr;
    }
}

void TilemapTool::Update()
{
    ProcessMouseMessage();
    if (saveButton) saveButton->Update();
    if (loadButton) loadButton->Update();
}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, TILEMAPTOOL_X, TILEMAPTOOL_Y, WHITENESS);

    for (int i = 0; i < TILE_X * TILE_Y; ++i)
    {
        sampleTile->FrameRender(hdc, tileInfo[i].rc.left, tileInfo[i].rc.top, tileInfo[i].frameX, tileInfo[i].frameY, false, false);
    }

    sampleTile->Render(hdc, TILEMAPTOOL_X - sampleTile->GetWidth(), 0);

    sampleTile->FrameRender(hdc, TILEMAPTOOL_X - sampleTile->GetWidth(), sampleTile->GetHeight() + 100, selectedTile.x, selectedTile.y, false, false);

    if (saveButton) saveButton->Render(hdc);
    if (loadButton) loadButton->Render(hdc);
}

void TilemapTool::ProcessMouseMessage()
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
    {
        POINT mouse;
        GetCursorPos(&mouse);
        ScreenToClient(g_hWnd, &mouse);
        
        // select tile
        if (PointInRect(mouse, rcSampleTile))
        {
            int posX = mouse.x - rcSampleTile.left;
            int posY = mouse.y - rcSampleTile.top;
            selectedTile.x = posX / TILE_SIZE;
            selectedTile.y = posY / TILE_SIZE;
        }
        // set tile
        else if (PointInRect(mouse, rcMain))
        {
            int posX = mouse.x;
            int posY = mouse.y;
            int tileX = posX / TILE_SIZE;
            int tileY = posY / TILE_SIZE;

            tileInfo[tileY * TILE_X + tileX].frameX = selectedTile.x;
            tileInfo[tileY * TILE_X + tileX].frameY = selectedTile.y;
        }

        //if (PointInRect(mouse, saveButton))
        //{
        //    SaveTilemap();
        //}
        //else if (PointInRect(mouse, loadButton))
        //{
        //    LoadTilemap();
        //}
    }
}

void TilemapTool::SaveTilemap()
{
    ofstream out{ "타일맵데이터.txt" };
    for (int i = 0; i < TILE_X * TILE_Y; ++i)
    {
        out << tileInfo[i].frameX << ' ' << tileInfo[i].frameY << '\n';
    }

    out.close();
}

void TilemapTool::LoadTilemap()
{
    ifstream in{ "타일맵데이터.txt" };
    for (int i = 0; i < TILE_X * TILE_Y; ++i)
    {
        in >> tileInfo[i].frameX >>tileInfo[i].frameY;
    }
}
