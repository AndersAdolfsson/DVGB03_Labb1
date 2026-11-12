#include "algorithm.h"

//
// Private
//
static void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

static void sort_part(int *a, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	int pivot = a[right];
	int boundary = left;

	for(int j = left; j < right; j++)
	{
		if(a[j] < pivot)
		{
			swap(&a[j], &a[boundary]);
			boundary++;
		}
	}
	swap(&a[right], &a[boundary]);
	sort_part(a, left, boundary - 1);
	sort_part(a, boundary + 1, right);
}
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
	for(int i = 1; i < n; i++)
	{
		int key = a[i];
		int j = i-1;
		
		while(j >= 0 && a[j] > key)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
}

void quick_sort(int *a, int n) 
{
	int left = 0;
	int right = n-1;

	sort_part(a, left, right);
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
	int left = 0;
	int right = n-1;
	
	while(left<=right)
	{
		int mid = left + (right-left) / 2;
		if(a[mid]==v)
		{
			return true;
		}
		else if(a[mid] < v)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return false; 
}
