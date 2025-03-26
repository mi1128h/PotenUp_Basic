#include <iostream>
#include "BulletFactory.h"

int main()
{
	BulletFactory* bulletFactoryList[3];
	bulletFactoryList[0] = new NormalBulletFactory();
	bulletFactoryList[1] = new SignBulletFactory();
	bulletFactoryList[2] = new LazerBulletFactory();

	for (int i = 0; i < 3; ++i) {
		bulletFactoryList[i]->AddBullet();
	}

	for (int i = 0; i < 3; ++i) {
		delete bulletFactoryList[i];
	}
}