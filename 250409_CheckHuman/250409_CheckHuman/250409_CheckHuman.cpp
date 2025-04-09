#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include <chrono>

using namespace std;

int main()
{
    chrono::system_clock::time_point start = chrono::system_clock::now();

    FILE* fp = nullptr;
    fopen_s(&fp, "마을2.txt", "r");

    if (fp == nullptr)
    {
        cout << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    unordered_map<int, vector<int>> vTotalList;

    int totalCount = 0;
    fscanf_s(fp, "%d", &totalCount);

    while (1)
    {
        if (feof(fp)) break;

        int id = 0;
        int answerCount = 0;
        fscanf_s(fp, "%d", &id);
        fscanf_s(fp, "%d", &answerCount);
        
        int answer = 0;
        vector<int> answerList;
        for (int i = 0; i < answerCount; ++i)
        {
            fscanf_s(fp, "%d", &answer);
            answerList.push_back(answer);
        }
        
        vTotalList[id] = answerList;
    }
    // 사람 확인 로직
    queue<int> checkList;
    unordered_set<int> trueHumanList;

    trueHumanList.insert(1);
    for (int d : vTotalList[1])
    {
        checkList.push(d);
    }

    while (!checkList.empty())
    {
        int human = checkList.front();
        checkList.pop();
        if (trueHumanList.find(human) != trueHumanList.end()) continue;

        trueHumanList.insert(human);
        for (int d : vTotalList[human])
        {
            checkList.push(d);
        }
    }

    // 진짜 사람 수 출력
    cout << trueHumanList.size();

    fclose(fp);

    chrono::duration<double> sec = chrono::system_clock::now() - start;
    cout << "\n걸린 시간: " << sec.count() << '\n';
}