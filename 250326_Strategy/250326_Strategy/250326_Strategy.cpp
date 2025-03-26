#include <iostream>
#include "SortManager.h"

int main()
{
	int testArr[10] = { 4, 32, 56, 2, 1, 0, 234, 98, -1, -8 };
	SortManager sortManager;

	sortManager.ChangeSort(std::make_unique<BubbleSort>());
	sortManager.DoSort(testArr);

	sortManager.ChangeSort(std::make_unique <QuickSort>());
	sortManager.DoSort(testArr);
	
	sortManager.ChangeSort(std::make_unique<MergeSort>());
	sortManager.DoSort(testArr);
}