#include "Sort.h"
#include <iostream>

void QuickSort::DoSort(int* arr)
{
	std::cout << "퀵정렬 알고리즘을 사용해서 정렬했다!" << std::endl;
}

void BubbleSort::DoSort(int* arr)
{
	std::cout << "버블정렬 알고리즘을 사용해서 정렬했다!" << std::endl;
}

void MergeSort::DoSort(int* arr)
{
	std::cout << "머지정렬 알고리즘을 사용해서 정렬했다!" << std::endl;
}
