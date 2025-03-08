#include <iostream>
#include <Windows.h>
#include <fstream>
#include "FileManager.h"

using namespace std;

class Car {	// 틀, 설계도
	// 멤버 변수 (field, 속성, 스테이트, 데이터)
private:
	float moveSpeed;
	float maxMoveSpeed;
	short gear;
	string color;
	RECT rc;

public:
	// 멤버 함수 (method, 동작, 기능, 함수)
	void Setup(float moveSpeed, float maxMoveSpeed, short gear, string color, RECT rc) {
		// (*this).moveSpeed = moveSpeed;
		this->moveSpeed = moveSpeed;
		this->maxMoveSpeed = maxMoveSpeed;
		this->gear = gear;
		this->color = color;
		this->rc = rc;
	}
	void SpeedUp();
	void SpeedDown();
	void ChangeGear();
	virtual void Run() { cout << "Car run"; };
	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom); // rc에 내적하는 원
	}
};

class DerivedCar :public Car {
	void Run() override { cout << "DerivedCar run"; }
};

int main()
{
	GameData gameData;
	//gameData.difficulty = 2;
	//gameData.exitPosX = 10;
	//gameData.exitPosY = 11;
	//gameData.playerPosX = 0;
	//gameData.playerPosY = 1;
	//gameData.playerGold = 200;

	FileManager fileManager;
	//fileManager.WriteFile("save_data.txt", gameData, true);
	fileManager.ReadFile("save_data.txt", gameData, true);
	
#ifdef DrawRECT
	Car car1, car2;
	car1.Setup(0.0f, 5.0f, 1, "빨간색", RECT{ 100, 100, 200, 200 });
	car2.Setup(0.0f, 10.0f, 1, "파란색", RECT{ 100, 100, 200, 200 });

	while (1) {
		car1.Draw();
		Sleep(500);
	}
#endif
}