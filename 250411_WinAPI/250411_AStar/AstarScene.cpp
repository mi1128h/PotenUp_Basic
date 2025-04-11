#include "AstarScene.h"
#include "CommonFunction.h"

HRESULT AstarTile::Init()
{
	return E_NOTIMPL;
}

HRESULT AstarTile::Init(int idX, int idY)
{
	this->idX = idX;
	this->idY = idY;

	center.x = idX * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);
	center.y = idY * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);

	rc.left = idX * ASTAR_TILE_SIZE;
	rc.right = rc.left + ASTAR_TILE_SIZE;
	rc.top = idY * ASTAR_TILE_SIZE;
	rc.bottom = rc.top + ASTAR_TILE_SIZE;

	costFromStart = 0.0f;
	costToGoal = 0.0f;
	totalCost = 0.0f;

	type = AstarTileType::None;

	parentTile = nullptr;

	color = RGB(100, 100, 100);
	hBrush = CreateSolidBrush(color);

	return S_OK;
}

void AstarTile::Release()
{
	DeleteObject(hBrush);
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	FillRect(hdc, &rc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, hOldBrush);
}

void AstarTile::SetColor(COLORREF color)
{
	this->color = color;
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(color);
}

void AstarTile::CalculateCost(const AstarTile* goal)
{
	if (!parentTile)
	{
		costFromStart = 0;
	}
	else
	{
		costFromStart = parentTile->costFromStart + GetDistance({ (float)parentTile->idX, (float)parentTile->idY }, { (float)idX, (float)idY });
	}
	costToGoal = GetDistance({ (float)goal->idX, (float)goal->idY }, { (float)idX, (float)idY });
	totalCost = costFromStart + costToGoal;
}

bool AstarTile::operator==(const AstarTile& other)
{
	if (idX == other.idX and idY == other.idY) return true;
	return false;
}

HRESULT AstarScene::Init()
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Init(j, i);
		}
	}

	startTile = &(map[3][3]);
	startTile->SetColor(RGB(255, 0, 0));
	startTile->SetType(AstarTileType::Start);

	currTile = startTile;

	destTile = &(map[10][19]);
	destTile->SetColor(RGB(0, 0, 255));
	destTile->SetType(AstarTileType::End);

	return S_OK;
}

void AstarScene::Release()
{
}

void AstarScene::Update()
{
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_RBUTTON))
	{
		// g_ptMouse로 인덱스를 계산
		int x, y;
		x = g_ptMouse.x / ASTAR_TILE_SIZE;
		y = g_ptMouse.y / ASTAR_TILE_SIZE;

		if (0 <= x && x < ASTAR_TILE_COUNT &&
			0 <= y && y < ASTAR_TILE_COUNT)
		{
			// 시작이나 목적지가 아닐 때
			if (map[y][x].GetType() != AstarTileType::Start &&
				map[y][x].GetType() != AstarTileType::End)
			{
				map[y][x].SetColor(RGB(100, 150, 100));
				map[y][x].SetType(AstarTileType::Wall);
			}
		}
	}

	// TODO 
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		MoveToDest();
	}
}

void AstarScene::Render(HDC hdc)
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Render(hdc);
		}
	}
}

void AstarScene::FindPath()
{
	if (currTile)
	{
		// 도착여부 판단
		if (currTile == destTile)
		{
			return;
		}
		else
		{
			openList.erase(remove(openList.begin(), openList.end(), currTile), openList.end());
			closeList.push_back(currTile);
		}

		// 주위에 있는 이동가능한 타일들을 F값 계산 후보에 넣는다.
		int dx[] = {  1, 1,  1, 0,  0, -1, -1, -1 };
		int dy[] = {  1, 0, -1, 1, -1,  1,  0, -1 };
		for (int i = 0; i < 8; ++i)
		{
			int nextX = currTile->GetIdX() + dx[i];
			int nextY = currTile->GetIdY() + dy[i];
			
			if (OutOfRange(nextX, nextY)) continue;

			AddOpenList(&map[nextY][nextX]);
		}

		if (openList.empty()) return;

		// 후보들 중 F값이 가장 작은 타일을 다음 currTile 선정
		auto minCostTile = min_element(openList.begin(), openList.end(), [](const AstarTile* a, const AstarTile* b) {
			return a->GetTotalCost() < b->GetTotalCost();
			});

		if (minCostTile != openList.end())
		{
			currTile = *minCostTile;
		}

		// 반복
		FindPath();
	}
}

void AstarScene::AddOpenList(AstarTile* neighborTile)
{
	if (find(closeList.begin(), closeList.end(), neighborTile) != closeList.end()) return;
	if (neighborTile->GetType() == AstarTileType::Wall) return;

	float originCostFromStart = neighborTile->GetCostFromStart();
	AstarTile* originParentTile = neighborTile->GetParentTile();

	neighborTile->SetParentTile(currTile);
	neighborTile->CalculateCost(destTile);

	if (find(openList.begin(), openList.end(), neighborTile) == openList.end())
	{
		openList.push_back(neighborTile);
	}
	else
	{
		if (originCostFromStart < neighborTile->GetCostFromStart())
		{
			if (originParentTile->GetType() != AstarTileType::Wall)
			{
				neighborTile->SetParentTile(originParentTile);
				neighborTile->CalculateCost(destTile);
			}
		}
	}
}

bool AstarScene::OutOfRange(int x, int y)
{
	if (x < 0 or x >= ASTAR_TILE_COUNT) return true;
	if (y < 0 or y >= ASTAR_TILE_COUNT) return true;
	return false;
}

void AstarScene::MoveToDest()
{
	if (startTile == destTile) return;

	openList.clear();
	closeList.clear();
	currTile = startTile;
	FindPath();

	stack<AstarTile*> path;
	AstarTile* tempTile = destTile;
	while (tempTile != startTile)
	{
		if (!tempTile->GetParentTile()) break;
		path.push(tempTile);
		tempTile = tempTile->GetParentTile();
	}

	if (path.size() > 0)
	{
		startTile->SetColor(RGB(100, 100, 100));
		startTile = path.top();
		startTile->SetColor(RGB(255, 0, 0));
	}
}
