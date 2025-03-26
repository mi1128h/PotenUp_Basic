#include <iostream>
#include "SortManager.h"

int main()
{
	int testArr[10] = { 4, 32, 56, 2, 1, 0, 234, 98, -1, -8 };
	SortManager sortManager;

	sortManager.ChangeSort(new BubbleSort());
	sortManager.DoSort(testArr);

	sortManager.ChangeSort(new QuickSort());
	sortManager.DoSort(testArr);
	
	sortManager.ChangeSort(new MergeSort());
	sortManager.DoSort(testArr);
}