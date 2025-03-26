#pragma once
#include "Sort.h"

class SortManager
{
public:
	SortManager() : sort(nullptr) {}
	~SortManager() { if (sort) delete sort; sort = nullptr; }

	void DoSort(int* arr)
	{
		if (sort)
		{
			sort->DoSort(arr);
		}
	}

	void ChangeSort(ISort* newSort)
	{
		if (sort) delete sort;
		sort = newSort;
	}

private:
	ISort* sort;
};

