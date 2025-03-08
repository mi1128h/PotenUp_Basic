#include <iostream>

using namespace std;

int main()
{
#pragma region 실습
    // 실습1. 고객의 나이를 입력 받아서
    // 미성년자(19살 이하)이면 false, 성년이면 true 출력
    // 주민등록발급대상(20살만) 이면 true, 아니면 false
    // 아홉수(1의 자리가 9)인지 확인해서 true, 아니면 false
    //
    //int customerAge{};
    //cin >> customerAge;
    //
    //cout << boolalpha;
    //cout << "성년인가? --> " << (customerAge > 19) << endl;
    //cout << "주민등록발급대상인가? --> " << (customerAge == 20) << endl;
    //cout << "아홉수인가? --> " << (customerAge % 10 == 9) << endl;
#pragma endregion

#pragma region 실습
    // 실습1. 3 ~ 7 사이의 랜덤한 값을 출력하는 프로그램 작성.
    // 실습2. 가장 작은 값과 가장 큰 값을 입력받아서 그 사이의 임의의 값을 출력
    // 실습3. 프로그램을 실행하면 프로그램이 1 ~ 10 사이의 숫자를 지정
    //       유저는 1 ~ 10 사이의 숫자를 입력
    //       맞으면 true, 틀리면 false 출력
    //srand(time(NULL));
    //int randNum = rand();

    //cout << "3 ~ 7 사이의 랜덤값: " << rand() % 5 + 3 << endl;
    //
    //int minNum{}, maxNum{};
    //cout << "최솟값 입력: ";
    //cin >> minNum;
    //cout << "최댓값 입력: ";
    //cin >> maxNum;
    //cout << "임의의 값: " << rand() % (maxNum - minNum + 1) + minNum << endl;

    //int answer = rand() % 10 + 1;
    //cout << "1 ~ 10 사이의 숫자 입력: ";
    //int userAnswer{};
    //cin >> userAnswer;
    //cout << boolalpha << (answer == userAnswer) << "! answer was " << answer << endl;
#pragma endregion

#pragma region 실습
    // 정수를 하나 입력 받아서
    // 입력받은 정수가 10보다 크면 "입력된 숫자가 10보다 큽니다."
    // 입력받은 정수가 9 초과이면 "입력된 숫자가 9보다 큽니다."
    // 입력받은 정수가 6 초과이면 "입력된 숫자가 6보다 큽니다."
    // 그 이외에는 "입력된 숫자가 6보다 작거나 같습니다."
    //
    //int d;
    //cout << "숫자 입력: ";
    //cin >> d;
    //if (d > 10) cout << "입력된 숫자가 10보다 큽니다.";
    //else if (d > 9) cout << "입력된 숫자가 9보다 큽니다.";
    //else if (d > 6) cout << "입력된 숫자가 6보다 큽니다.";
    //else cout << "입력된 숫자가 6보다 작거나 같습니다.";
#pragma endregion

#pragma region for문
    /*
    // 1부터 10까지 순차적으로 증가시킨 값을 출력
    for (int i = 0; i < 10; ++i) {
        cout << i + 1 << endl;
    }

    // 10부터 1까지 차례대로 출력
    for (int i = 10; i > 0; --i) {
        cout << i << endl;
    }
    */

    // 실습1. 100 미만의 3의 배수를 차례대로 출력
    // 실습2. 1000 미만의 2의 승수를 차례대로 출력
    /*
    for (int i = 3; i < 100; i += 3) cout << i << ' ';
    cout << endl;

    for (int i = 2; i < 1000; i *= 2) cout << i << ", ";
    cout << endl << endl;

    int d = 3;
    while (d < 100) {
        cout << d << ' ';
        d += 3;
    }
    cout << endl;

    d = 2;
    while (d < 1000) {
        cout << d << ", ";
        d *= 2;
    }
    cout << endl << endl;

    d = 3;
    do {
        cout << d << ' ';
        d += 3;
    } while (d < 100);
    cout << endl;

    d = 2;
    do {
        cout << d << ", ";
        d *= 2;
    } while (d < 1000);
    */

    // 구구단 2 ~ 9단
    /*
    for (int i = 2; i < 10; ++i) {
        for (int j = 1; j < 10; ++j) {
            cout << i << " * " << j << " = " << i * j << endl;
        }
        cout << endl;
    }

    for (int j = 1; j < 10; ++j) {
        for (int i = 2; i < 10; ++i) {
            cout << i << " * " << j << " = " << i * j << '\t';
        }
        cout << endl;
    }
    */

    // 2단 3단 4단
    // 5단 6단 7단
    // 8단 9단
    for (int i = 2; i < 10; i+=3) {
        for (int j = 1; j < 10; ++j) {
            for (int k = i; k < i + 3; ++k) {
                if (k == 10) break;
                cout << k << " * " << j << " = " << k * j << '\t';
            }
            cout << endl;
        }
        cout << endl;
    }
    
#pragma endregion
}