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
}

void MissileManager::Update()
{
}

void MissileManager::Render(HDC hdc)
{
}
