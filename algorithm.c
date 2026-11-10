#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n) 
{
	for(int i = 0; i < n-1; i++)
	{
		bool swapped = false;

		for(int j = 0; j < n-1; j++)
		{
			if(a[j] > a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swapped = true;
			}
		}
		if(swapped==false)
		{
			break;
		}
	}
}

void insertion_sort(int *a, int n) 
{
	// TODO: insertion sort
	//
}

void quick_sort(int *a, int n) 
{
	// TODO: quick sort
}

bool linear_search(const int *a, int n, int v)
{
	for(int i = 0; i < n; i++)
	{
		if(a[i] == v)
		{
			return true;
		}
	}
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
