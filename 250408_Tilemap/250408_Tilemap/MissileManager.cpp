#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	vecMissiles.resize(30);
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end(); iterMissiles++)
	{
		(*iterMissiles) = new Missile();
		(*iterMissiles)->Init();
	}

	return S_OK;
}

void MissileManager::Release()
{
	for (auto& missile : vecMissiles)
	{
		if (missile)
		{
			missile->Release();
			delete missile;
			missile = nullptr;
		}
	}
	vecMissiles.clear();
}

void MissileManager::Update()
{
}

void MissileManager::Render(HDC hdc)
{
}
