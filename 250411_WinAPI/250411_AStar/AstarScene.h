#pragma once
#include "GameObject.h"
#include "config.h"

/*
	���� ��� : Ž���� ������ ����, ���� ��� �߰�
	���� ��� : �̹� Ž���� ������ ����, �ʱ⿡�� ��� ����
	g(n) : ���� ��忡�� ��� n���� �̵��ϴ� ���� ��� 
	h(n) : ��� n���� ��ǥ �������� �������(�޸���ƽ)
	f(n) : ��� n���� ��ǥ ���� �����ϴ� �� ���, f(n) = g(n) + h(n)

	Ž�� ���� :
	 1) ���� ��Ͽ��� f���� ���� ���� ��� n�� �����ؼ� ���� ���� ����
	 2) ���� ��� n�� ��ǥ����� ��� Ž���� �����ϰ�, ��θ� ��ȯ
	 3) �׷��� ������, ���� ��带 ���� ��Ͽ��� �����ϰ� ���� ��Ͽ� �߰�
	 4) ���� ��� n�� ���� ��� �̿���� m�� ���ؼ� ���� �ܰ踦 ����
		4_1) m�� ���� ��Ͽ� ������ ����
		4_2) m�� ���� ��Ͽ� ������ �߰�( g(m), h(m), f(m) / 
			�θ� ���(���� ���)�� n���� ����)
		4_3) m�� �̹� ���� ��Ͽ� �ְ�, ���� ��θ� ���ؼ� �� ���� g����
			���� �� �ִٸ�, g(m), f(m)���� , �θ� ��嵵 ����

	��� ���� :
	��ǥ ��忡�� ���� ������ �θ��带 ��θ� �������ؼ� ��� ����
*/

#define ASTAR_TILE_SIZE		30
#define ASTAR_TILE_COUNT	20

enum class AstarTileType { Start, End, Wall, None };

class AstarTile : public GameObject
{
private:
	int idX, idY;
	POINT center;
	RECT rc;
	AstarTileType type;

	float costFromStart;	// g : ���������� ���� �������� ���
	float costToGoal;		// h : ���� ������ ������������ ������
	float totalCost;		// f : g + h

	AstarTile* parentTile;	// g�� ���ŵ� ������ ���� ��带 ����

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

public:
	virtual HRESULT Init();
	HRESULT Init(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetColor(COLORREF color);
	void SetType(AstarTileType type) { this->type = type; }
	AstarTileType GetType() { return this->type; }

	virtual ~AstarTile() {};

};

class AstarScene : public GameObject
{
	// ������ �迭 ���� ����
	AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];

	AstarTile* startTile;	// ������
	AstarTile* destTile;	// �Ķ���

	AstarTile* currTile;	// (���) �ĺ�Ÿ���� ������ ���� ����Ÿ��

	vector<AstarTile*> openList;
	vector<AstarTile*> closeList;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void FindPath();
	void AddOpenList(AstarTile* currTile);

	virtual ~AstarScene() {};
};

