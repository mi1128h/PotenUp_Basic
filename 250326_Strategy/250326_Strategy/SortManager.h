#pragma once
#include "Sort.h"
#include <memory>

class SortManager
{
public:
	SortManager() : sort(nullptr) {}
	~SortManager() {}

	void DoSort(int* arr)
	{
		if (sort)
		{
			sort->DoSort(arr);
		}
	}

	void ChangeSort(std::unique_ptr<ISort> newSort)
	{
		sort = move(newSort);
	}

private:
	std::unique_ptr<ISort> sort;
};

