#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int main()
{
#pragma region 구구단
	//int arrNum[10];
	//arrNum[0] = 1;

	// 1차원 배열 한 반에 있는 5명의 학생
	//string arrStudentName[5];

	// 2차원 배열 한 학년에 3개 반에 있는 총 15명의 학생
	//string arrStudentName[3][5];

	// 3차원 배열 학교에 4개 학년, 학년에 3개 반, 각 반에 5명
	//string arrStudentName[4][3][5];

	// 구구단의 결과를 저장하는 2차원 배열 guguDatas
	// 두 수를 입력 받아서 해당하는 결과를 출력
	/*
	int guguDatas[8][9]{};
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 9; ++j) {
			guguDatas[i][j] = (i + 2) * (j + 1);
		}
	}
	int a, b;
	cout << "몇 단: ";
	cin >> a;
	cout << "곱할 수: ";
	cin >> b;
	cout << "결과: " << guguDatas[a - 2][b - 1] << endl;
	*/
#pragma endregion

#pragma region 메모리주소, 문자 입력
	/*
	int num = 3;
	// 1) 이름	2) 타입	3) 값	4) 메모리주소
	cout << &num << endl;

	int nums[5]{ 1,2,3,4,5 };
	cout << nums << endl;
	cout << &nums[0] << endl;
	cout << nums + 1 << endl;
	cout << &nums[1] << endl;
	*/
	/*
	char inputKey = 'A';	// ASCII code
	cout << (int)inputKey << endl;

	// 문자 입력 받는 방법
	int inputKey = _getch();
	cout << (int)inputKey << endl;
	*/
#pragma endregion

#pragma region 실습. 알파벳 맞히기
	// 실습 A ~ Z키 중에 임의의 값을 컴퓨터가 설정한다.
	// 유저는 한 개의 키를 입력해서 설정된 값을 맞춘다.
	// 유저가 입력한 키와 설정된 키가 같으면 승리!
	// 틀리면 남은 기회를 보여주고 5번 틀리면 정답을 알려주고 게임 오버
	// 틀릴 때마다 정답이 입력된 알파벳 앞에 있는지, 뒤에 있는지 알려준다
	/*
	srand(time(NULL));
	int chance = 5;
	const char comAlpha = rand() % ('Z' - 'A' + 1) + 'A';
	while (chance >= 0) {
		if (chance == 0) {
			cout << "게임 오버" << endl;
			cout << "정답은: " << comAlpha << endl;
			break;
		}
		cout << "A ~ Z키 중 하나를 누르세요: ";
		int inputKey = _getch();
		inputKey = toupper(inputKey);
		cout << (char)inputKey << endl;
		if (inputKey == comAlpha) {
			cout << "정답입니다 " << comAlpha << endl;
			break;
		}
		else if (inputKey > comAlpha) {
			cout << "입력한 알파벳보다 앞에 있습니다." << endl;
		}
		else {
			cout << "입력한 알파벳보다 뒤에 있습니다." << endl;
		}
		--chance;
		if (chance == 0) continue;
		cout << "남은 기회: " << chance << endl;
	}
	*/
#pragma endregion

#pragma region 실습. 탈출 게임
	// 탈출게임
	// 10 * 10 2차원 배열로 맵을 만든다. (#으로 출력한다)
	// WASD 키로 플레이어 (O)가 상하좌우로 이동한다.
	// 플레이어의 시작 지점은 {0, 0}, 탈출 지점은 {0, 0}을 제외한 랜덤 설정
	// 플레이어가 탈출 지점에 도착하면 "탈출에 성공했습니다. 승리!" 출력하고 종료
	const int BOARD_SIZE = 10;
	int playerX{}, playerY{};
	int goalX{}, goalY{};
	while ((goalX | goalY) == 0) {
		goalX = rand() % BOARD_SIZE;
		goalY = rand() % BOARD_SIZE;
	}

	int arrMap[BOARD_SIZE][BOARD_SIZE]{};
	arrMap[playerY][playerX] = 1;
	arrMap[goalY][goalX] = -1;

	while (true) {
		system("cls");
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (arrMap[i][j] == -1) cout << 'E';
				else cout << (arrMap[i][j] ? 'O' : '#');
			}
			cout << endl;
		}

		if (playerX == goalX and playerY == goalY) {
			cout << "탈출에 성공했습니다. 승리!" << endl;
			break;
		}

		int inputKey = _getch();

		int dx{}, dy{};
		switch (inputKey) {
		case 'W': case 'w':
			if (playerY == 0) continue;
			dy = -1;
			break;
		case 'S': case 's':
			if (playerY == BOARD_SIZE - 1) continue;
			dy = 1;
			break;
		case 'A': case 'a':
			if (playerX == 0) continue;
			dx = -1;
			break;
		case 'D': case 'd':
			if (playerX == BOARD_SIZE - 1) continue;
			dx = 1;
			break;
		}

		arrMap[playerY][playerX] = 0;
		playerX += dx;
		playerY += dy;
		arrMap[playerY][playerX] = 1;
	}
#pragma endregion


}