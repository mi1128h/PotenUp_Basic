﻿#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// : 다음 구조로 생성
//               [3]------3------[5]      
//                |              / \      
//                |             /   \     
//                4            3     4    
//                |           /       \   
//                |          /         \  
// [1]-----2-----[2]---1---[4]         [8]
//   \                       \         /  
//    \                       \       /   
//     3                       2     4    
//      \                       \   /     
//       \                       \ /      
//       [6]----------6----------[7]   

#define I 100
#define NUM_NODE 8
int edgeCost[NUM_NODE][NUM_NODE] =
{
	{ 0,2,I,I,I,3,I,I },//1
	{ 2,0,4,1,I,I,I,I },//2
	{ I,4,0,I,3,I,I,I },//3
	{ I,1,I,0,3,I,2,I },//4
	{ I,I,3,3,0,I,I,4 },//5
	{ 3,I,I,I,I,0,6,I },//6
	{ I,I,I,2,I,6,0,4 },//7
	{ I,I,I,I,4,I,4,0 },//8
};

stack<int> Dijkstra(int start, int end);

bool OutOfRange(int start, int end)
{
	if (start < 1 or end < 1) return true;
	if (start > NUM_NODE or end > NUM_NODE) return true;
	return false;
}

int main()
{
	int startNode{}, endNode{};
	cout << "시작 노드: ";
	cin >> startNode;
	cout << "도착 노드: ";
	cin >> endNode;

	if (OutOfRange(startNode, endNode))
	{
		cout << "잘못된 범위 입력" << endl;
		return 1;
	}

	stack<int> route = Dijkstra(startNode - 1, endNode - 1);

	cout << "루트: ";
	while (!route.empty())
	{
		cout << route.top() << ' ';
		route.pop();
	}
	cout << endl;
}

stack<int> Dijkstra(int start, int end)
{
	vector<int> minList;
	minList.resize(NUM_NODE, INT_MAX);
	vector<bool> visitList;
	visitList.resize(NUM_NODE, false);
	vector<int> parentList;
	parentList.resize(NUM_NODE, -1);
	parentList[start] = start;

	queue<int> q;
	q.push(start);
	minList[start] = 0;

	while (!q.empty())
	{
		int node = q.front(); q.pop();
		visitList[node] = true;
		for (int i = 0; i < NUM_NODE; ++i)
		{
			if (!visitList[i])
			{
				if (edgeCost[node][i] + minList[node] < minList[i])
				{
					minList[i] = edgeCost[node][i] + minList[node];
					parentList[i] = node;
				}
			}
		}

		int minCost{ INT_MAX };
		int idx{ -1 };
		for (int i = 0; i < NUM_NODE; ++i)
		{
			if (visitList[i]) continue;
			if (minCost > minList[i])
			{
				minCost = minList[i];
				idx = i;
			}
		}

		if(idx != -1) q.push(idx);
	}

	stack<int> route;
	int nextRoute = end;
	while (true)
	{
		route.push(nextRoute + 1);
		if (nextRoute == parentList[nextRoute]) break;
		nextRoute = parentList[nextRoute];
	}

	cout << "비용: " << minList[end] << endl;;

	return route;
}