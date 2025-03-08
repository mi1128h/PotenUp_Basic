#include <iostream>
#include <vector>
using namespace std;

#ifdef 구조체 설명
typedef struct Weapon
{
	string name;
	double attackValue;
	int price;
} WEAPON, weapon_info;

struct Player
{
	string name;
	float moveSpeed;
	double attackValue;
	int hp;
	bool isDead;
};
#endif

#ifdef 함수 설명
// 두 정수를 합한 결과를 반환하는 함수
int Add(int a, int b)
{
	return a + b;
}

// 두 실수를 합한 결과를 반환하는 함수
float Add(float a, float b)
{
	return a + b;
}

// 리턴 타입이 없는 경우, ex) 매개변수로 전달 받은 두 변수의 값을 스왑한다.
void Swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}


// 매개변수가 없는 경우, ex) 화면에 텍스트를 출력
bool PrintHelloWorld()
{
	cout << "Hello, World!" << endl;
	return true;
}
#endif

#ifdef 실습
void PrintIsAdult(int age)
{
	cout << (age > 19 ? "성인" : "미성년자") << "입니다\n";
}

float Avg(int a, int b)
{
	return (float)(a + b) / 2.0f;
}

// 매개변수로 정수를 하나 입력 받아서 그 정수를 50으로 바꾸는 함수, 리턴타입 void
void ChangeNumTo50(int* n)
{
	*n = 50;
}

void ChangeNumTo50(int& n)
{
	n = 50;
}

void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
#endif

int main()
{
#ifdef 실습
	// 실습1. 나이를 입력 받아서 미성년자인지 아닌지 텍스트로 출력하는 함수
	// 실습2. 두 정수를 입력 받아서 두 수의 평균(실수)을 반환하는 함수
	int userAge;
	cin >> userAge;
	PrintIsAdult(userAge);

	int d1, d2;
	cin >> d1 >> d2;
	cout << Avg(d1, d2);

	// 지역변수: 변수가 선언된 코드 묶음에서만 라이프 사이클이 존재하는 변수
	int attack = 10;
	ChangeNumTo50(&attack);
	cout << attack << '\n';

	int a = 10, b = 20;
	Swap(&a, &b);
	cout << a << ' ' << b;
#endif
	/*
	탈출맵 확장 및 리팩토링 ( 배열 / 구조체 / 함수를 최대한 활용 )
	맵의 구성: 타일
	타일에는 종류가 있다. (땅, 숲, 늪)마다 만나는 몬스터가 달라진다.
	타일: x, y, 타입, 모양
	플레이어: 이름, 최대HP (레벨에 따라 달라진다), HP, 경험치, 레벨, 소유 골드
	몬스터: 이름, 최대HP, HP, 획득할 수 있는 경험치, 골드
	물약: 이름, 가격, 회복량
	상점: 물약 종류와 수량
	+ 추가 구현 마음대로
	*/
}