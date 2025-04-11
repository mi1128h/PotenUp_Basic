#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include <functional>

HRESULT TilemapTool::Init()
{
	SetClientRect(g_hWnd, TILEMAPTOOL_X, TILEMAPTOOL_Y);

	sampleTile = ImageManager::GetInstance()->AddImage(
		"��Ʋ��Ƽ_����Ÿ��", L"Image/mapTiles.bmp", 640, 288,
		SAMPLE_TILE_X, SAMPLE_TILE_Y);

	// ���� Ÿ�� ����
	rcSampleTile.left = TILEMAPTOOL_X - sampleTile->GetWidth();
	rcSampleTile.top = 0;
	rcSampleTile.right = TILEMAPTOOL_X;
	rcSampleTile.bottom = sampleTile->GetHeight();

	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
		{
			tileInfo[i * TILE_X + j].frameX = 3;
			tileInfo[i * TILE_X + j].frameY = 0;
			tileInfo[i * TILE_X + j].rc.left = j * TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.top = i * TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.right = 
				tileInfo[i * TILE_X + j].rc.left + TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.bottom = 
				tileInfo[i * TILE_X + j].rc.top + TILE_SIZE;
		}
	}

	// ���� Ÿ�� ����
	rcMain.left = 0;
	rcMain.top = 0;
	rcMain.right = TILE_X * TILE_SIZE;
	rcMain.bottom = TILE_Y * TILE_SIZE;

	// UI - ��ư
	saveButton = new Button();
	saveButton->Init(
		TILEMAPTOOL_X - sampleTile->GetWidth() + 180,
		sampleTile->GetHeight() + 100);
	//saveButton->SetFunction(&TilemapTool::Save, this);
	//saveButton->SetFunction(std::bind(&TilemapTool::Save, this));
	saveButton->SetFunction([this]() {
		this->Save();
		});

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
}

void TilemapTool::Update()
{
	if (PtInRect(&rcSampleTile, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSampleTile.left;
			int posY = g_ptMouse.y - rcSampleTile.top;
			selectedTile.x = posX / TILE_SIZE;
			selectedTile.y = posY / TILE_SIZE;
		}
	}
	else if (PtInRect(&rcMain, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x;
			int posY = g_ptMouse.y;
			int tileX = posX / TILE_SIZE;
			int tileY = posY / TILE_SIZE;
			tileInfo[tileY * TILE_X + tileX].frameX = selectedTile.x;
			tileInfo[tileY * TILE_X + tileX].frameY = selectedTile.y;
		}
	}

	if (saveButton)	saveButton->Update();
}

void TilemapTool::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, TILEMAPTOOL_X, TILEMAPTOOL_Y, WHITENESS);

	// ���� Ÿ�� ����
	for (int i = 0; i < TILE_X * TILE_Y; ++i)
	{
		sampleTile->FrameRender(hdc, tileInfo[i].rc.left,
			tileInfo[i].rc.top, tileInfo[i].frameX,
			tileInfo[i].frameY, false, false);
	}

	// ���� Ÿ�� ����
	sampleTile->Render(hdc, TILEMAPTOOL_X - sampleTile->GetWidth(), 0);

	// ���õ� Ÿ��
	sampleTile->FrameRender(hdc, 
		TILEMAPTOOL_X - sampleTile->GetWidth(),
		sampleTile->GetHeight() + 100,
		selectedTile.x, selectedTile.y, false, false);

	if (saveButton) saveButton->Render(hdc);
}

void TilemapTool::Save()
{
	// ���� ����
	HANDLE hFile = CreateFile(
		L"TileMapData.dat", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, TEXT("���� ���� ����"), TEXT("���"), MB_OK);
		return;
	}
	DWORD dwByte = 0;
	WriteFile(hFile, tileInfo, sizeof(tileInfo), &dwByte, NULL);
	CloseHandle(hFile);
}

void TilemapTool::Load()
{	
	// ���� �ε�
	HANDLE hFile = CreateFile(
		L"TileMapData.dat", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, TEXT("���� ���� ����"), TEXT("���"), MB_OK);
		return;
	}
	DWORD dwByte = 0;
	if (!ReadFile(hFile, tileInfo, sizeof(tileInfo), &dwByte, NULL))
	{
		MessageBox(g_hWnd, TEXT("���� �б� ����"), TEXT("���"), MB_OK);
	}
	CloseHandle(hFile);
}
