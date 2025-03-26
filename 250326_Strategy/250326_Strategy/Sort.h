#pragma once
class ISort
{
public:
	virtual ~ISort() {}

	virtual void DoSort(int* arr) = 0;
};

class QuickSort : public ISort
{
public:
	virtual ~QuickSort() {};

	virtual void DoSort(int* arr);
};

class BubbleSort : public ISort
{
public:
	virtual ~BubbleSort() {}

	virtual void DoSort(int* arr);

};

class MergeSort : public ISort
{
public:
	virtual ~MergeSort() {}

	virtual void DoSort(int* arr);

};