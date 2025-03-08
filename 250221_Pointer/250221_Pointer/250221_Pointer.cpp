#include <iostream>
#include <conio.h>
#include <vector>
//#define 역참조
//#define 동적할당new
//#define 실습_구구단
//#define 실습_구구단2
//#define 반복횟수
//#define 변수들의값
#define 실습_탈출게임2

using namespace std;

int main()
{
#ifdef 역참조
	int num = 3;
	int* pNum = &num;
	int** ppNum = &pNum;

	cout << "num 변수의 값: " << num << endl;
	cout << "num 변수의 크기: " << sizeof(num) << endl;
	cout << "num 변수의 주소1: " << &num << endl;
	cout << "num 변수의 주소2: " << pNum << endl;
	cout << endl;

	cout << "pNum 변수의 값: " << pNum << endl;
	cout << "pNum 변수의 크기: " << sizeof(pNum) << endl;
	cout << "pNum 변수의 주소: " << &pNum << endl;
	cout << "pNum 변수의 역참조: " << *pNum << endl;
	cout << endl;

	cout << "ppNum 변수의 값: " << ppNum << endl;
	cout << "ppNum 변수의 역참조: " << *ppNum << endl;
	cout << "ppNum 변수의 역참조의 역참조: " << **ppNum << endl;
#endif

#ifdef 동적할당new
	int* pTest = new int;	// 힙 메모리에 int 데이터 타입(4byte)만큼 메모리 할당을 받는다
	cout << "pTest 힙 메모리 할당 주소: " << pTest << endl;
	cout << "pTest 힙 메모리 할당 주소의 값: " << *pTest << endl;
	delete pTest;	// delete를 잊으면 메모리 누수가 발생한다

	int mapSize;
	cin >> mapSize;
	int* arrTest = new int[mapSize];
	delete[] arrTest;
#endif

#ifdef 실습_구구단
	/*
	구구단을 몇 단부터 몇 단까지 저장할까요? 2 6
	"2단부터 6단까지 저장 완료" 출력
	몇 단을 보여줄까요? 5
	5단 출력
	*/

	int guguStart{}, guguEnd{};
	cout << "구구단을 몇 단부터 몇 단까지: ";
	cin >> guguStart >> guguEnd;
	if (guguStart > guguEnd) swap(guguStart, guguEnd);

	int** arrGugu = new int* [guguEnd - guguStart + 1] {};
	for (int i = 0; i < guguEnd - guguStart + 1; ++i) {
		arrGugu[i] = new int[9] {};
		for (int j = 0; j < 9; ++j) {
			arrGugu[i][j] = (guguStart + i) * (j + 1);
		}
	}
	cout << guguStart << "단부터 " << guguEnd << "단까지 저장 완료\n";

	cout << "몇 단을 보여줄까요?: ";
	int dan{};
	cin >> dan;

	if (dan < guguStart or dan > guguEnd) {
		cout << "저장되지 않은 단입니다!\n";
	}
	else {
		for (int i = 0; i < 9; ++i) {
			cout << dan << " * " << i + 1 << " = " << arrGugu[dan - guguStart][i] << '\n';
		}
	}

	for (int i = 0; i < guguEnd - guguStart + 1; ++i) {
		delete[] arrGugu[i];
	}
	delete[] arrGugu;

#endif

#ifdef 실습_구구단2
	/*
	구구단을 몇 단부터 몇 단까지 저장할까요? 2 6
	"2단부터 6단까지 저장 완료" 출력
	몇 단을 보여줄까요? 5
	5단 출력
	*/

	int guguStart{}, guguEnd{};
	cout << "구구단을 몇 단부터 몇 단까지: ";
	cin >> guguStart >> guguEnd;
	if (guguStart > guguEnd) swap(guguStart, guguEnd);

	int size = guguEnd - guguStart + 1;
	int* arrGugu[9];
	for (int i = 0; i < 9; ++i) {
		arrGugu[i] = new int[size];
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < size; ++j) {
			arrGugu[i][j] = (i + 1) * (j + guguStart);
		}
	}
	cout << guguStart << "단부터 " << guguEnd << "단까지 저장 완료\n";

	cout << "몇 단을 보여줄까요?: ";
	int dan{};
	cin >> dan;

	if (dan < guguStart or dan > guguEnd) {
		cout << "저장되지 않은 단입니다!\n";
	}
	else {
		for (int i = 0; i < 9; ++i) {
			cout << dan << " * " << i + 1 << " = " << arrGugu[i][dan - guguStart] << '\n';
		}
	}

	for (int i = 0; i < 9; ++i) {
		delete[] arrGugu[i];
	}

#endif


#ifdef 반복횟수
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

	int n = 5;
	while (--n) {
		sum1++;
	}

	while (n--) {
		sum2++;
	}

	n = 4;
	do {
		sum3++;
	} while (n--);

	n = 3;
	for (int i = 0; i < n; ++i) {
		sum4++;
	}

	cout << sum1 << ' ' << sum2 << ' ' << sum3 << ' ' << sum4;
	// sum1, sum2, sum3, sum4를 크기가 큰 순서대로 나열하시오.
#endif

#ifdef 변수들의값
	int arr[3] = { 1,1,2 };
	arr[0];
	arr[1];
	*(arr);

	int a = 1;
	int b = 2;

	int* p1 = &a;
	int* p2 = &b;

	int** pp1 = &p1;
	int** pp2 = &p2;

	int* tp = *pp1;
	*pp1 = *pp2;
	*pp2 = tp;

	cout << a << ' ' << b << ' '
		<< *p1 << ' ' << *p2 << ' '
		<< **pp1 << ' ' << **pp2;
#endif


#ifdef 실습_탈출게임2
	// 탈출게임
	// 10 * 10 2차원 배열로 맵을 만든다. (#으로 출력한다)
	// WASD 키로 플레이어 (O)가 상하좌우로 이동한다.
	// 플레이어의 시작 지점은 {0, 0}, 탈출 지점은 {0, 0}을 제외한 랜덤 설정
	// 플레이어가 탈출 지점에 도착하면 "탈출에 성공했습니다. 승리!" 출력하고 종료

	// 난이도 선택 기능 추가(easy, normal, hard)
	// - 맵 사이즈 변화
	// - 적 수량 증가
	// 적 등장 및 이동

	const char CHAR_PLAYER = 'O';
	const char CHAR_MAP = '-';
	const char CHAR_GOAL = 'E';
	const char CHAR_MONSTER = 'M';

	const int BOARD_SIZE[3]{ 10,15,20 };
	const int ENEMY_NUM[3]{ 2,4,6 };

	int lv{};
	while (lv < 1 or lv > 3) {
		system("cls");
		cout << "1. easy  2. normal  3. hard\n"
			<< "난이도 선택: ";
		cin >> lv;
	}
	--lv;	// 0, 1, 2

	// locate player, goal
	int playerX{}, playerY{};
	int goalX{}, goalY{};
	int loop{};
	while ((goalX | goalY) == 0) {
		if (loop > 100) {	// unlucky,,,
			goalX = 7;
			goalY = 7;
		}
		goalX = rand() % BOARD_SIZE[lv];
		goalY = rand() % BOARD_SIZE[lv];
		loop++;
	}

	// create map
	vector<pair<int, int>> eLocRange;
	char** arrMap = new char* [BOARD_SIZE[lv]] {};
	for (int i = 0; i < BOARD_SIZE[lv]; ++i) {
		arrMap[i] = new char[BOARD_SIZE[lv]] {};
		for (int j = 0; j < BOARD_SIZE[lv]; ++j) {
			arrMap[i][j] = CHAR_MAP;
			if (i == 0 and j == 0) continue;
			if (i == goalX and j == goalY) continue;
			eLocRange.push_back({ i,j });
		}
	}

	// create enemy
	int* enemyX = new int[ENEMY_NUM[lv]] {};
	int* enemyY = new int[ENEMY_NUM[lv]] {};
	for (int i = 0; i < ENEMY_NUM[lv]; ++i) {
		int idx = rand() % eLocRange.size();
		enemyX[i] = eLocRange[idx].first;
		enemyY[i] = eLocRange[idx].second;
		eLocRange.erase(eLocRange.begin() + idx);
	}

	// display on board
	arrMap[playerY][playerX] = CHAR_PLAYER;
	arrMap[goalY][goalX] = CHAR_GOAL;
	for (int i = 0; i < ENEMY_NUM[lv]; ++i) {
		arrMap[enemyY[i]][enemyX[i]] = CHAR_MONSTER;
	}

	while (true) {
		// print map
		system("cls");
		for (int i = 0; i < BOARD_SIZE[lv]; ++i) {
			for (int j = 0; j < BOARD_SIZE[lv]; ++j) {
				cout << arrMap[i][j];
			}
			cout << endl;
		}

		// game clear
		if (playerX == goalX and playerY == goalY) {
			cout << "탈출에 성공했습니다. 승리!" << endl;
			break;
		}

		// game over
		bool collide = false;
		for (int i = 0; i < ENEMY_NUM[lv]; ++i) {
			if (playerX == enemyX[i] and playerY == enemyY[i]) {
				collide = true;
				break;
			}
		}

		if (collide) {
			cout << "몬스터에게 죽었습니다." << endl;
			break;
		}

		// move enemy
		for (int i = 0; i < ENEMY_NUM[lv]; ++i) {
			int edx{}, edy{};
			if (rand() % 2)	// horizontal move
				edx = rand() % 3 - 1;	// -1, 0, 1
			else
				edy = rand() % 3 - 1;

			if (enemyY[i] == goalY and enemyX[i] == goalX)	// redraw goal
				arrMap[enemyY[i]][enemyX[i]] = CHAR_GOAL;
			else
				arrMap[enemyY[i]][enemyX[i]] = CHAR_MAP;

			enemyX[i] += edx;
			enemyY[i] += edy;
			//enemyX[i] = clamp(enemyX[i], 0, BOARD_SIZE[lv]);	// C++17...
			if (enemyX[i] < 0) enemyX[i] = 0;
			if (enemyX[i] >= BOARD_SIZE[lv]) enemyX[i] = BOARD_SIZE[lv] - 1;
			if (enemyY[i] < 0) enemyY[i] = 0;
			if (enemyY[i] >= BOARD_SIZE[lv]) enemyY[i] = BOARD_SIZE[lv] - 1;

			arrMap[enemyY[i]][enemyX[i]] = CHAR_MONSTER;
		}

		// move player
		int inputKey = _getch();

		int dx{}, dy{};
		switch (inputKey) {
		case 'W': case 'w':
			dy = -1;
			break;
		case 'S': case 's':
			dy = 1;
			break;
		case 'A': case 'a':
			dx = -1;
			break;
		case 'D': case 'd':
			dx = 1;
			break;
		}

		if (arrMap[playerY][playerX] == CHAR_PLAYER)
			arrMap[playerY][playerX] = CHAR_MAP;

		playerX += dx;
		playerY += dy;
		if (playerX < 0) playerX = 0;
		if (playerX >= BOARD_SIZE[lv]) playerX = BOARD_SIZE[lv] - 1;
		if (playerY < 0) playerY = 0;
		if (playerY >= BOARD_SIZE[lv]) playerY = BOARD_SIZE[lv] - 1;

		if (arrMap[playerY][playerX] == CHAR_MAP)
			arrMap[playerY][playerX] = CHAR_PLAYER;
	}

	// delete map
	for (int i = 0; i < BOARD_SIZE[lv]; ++i) {
		delete[] arrMap[i];
	}
	delete[] arrMap;

	// delete enemy
	delete[] enemyX;
	delete[] enemyY;
#endif
}