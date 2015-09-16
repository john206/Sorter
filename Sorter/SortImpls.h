#include "stdafx.h"
#include <vector>

using namespace std;

void BubbleSort(vector<int> &arr, int start, int size) //algolist.net/Algorithms/Sorting/Bubble_sort
{
	int i = 0;
	bool swapped = true;

	while (swapped)
	{
		i++;
		swapped = false;		

		for (int j = 0; j <= size - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
	}
}

void InsertSort(vector<int> &arr, int start, int size) //algolist.net/Algorithms/Sorting/Insertion_sort
{
	int i, j, temp;
	for (i = start; i <= size; i++)
	{
		temp = arr[i];
		for (j = i - 1; j >= start && arr[j] > temp; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
	
	//Inefficient from algolist.net
	/*int i, j;

	for (i = 1; i <= size; i++)
	{
		j = i;

		while (j > 0 && arr[j - 1] > arr[j])
		{
			swap(arr[j], arr[j - 1]);
			j--;
		}
	}*/

	//Carrano -- does't work
	/*for (int unsorted = 1; unsorted <= size; unsorted++)
	{
		int nextItem = arr[unsorted];
		int loc = unsorted;
		
		while ((loc > 0) && (arr[loc - 1] > nextItem))
		{
			arr[loc] = arr[loc - 1];
		}

		arr[loc] = nextItem;
		loc--;
	}*/
	
}

void SortFirstMidLast(vector<int> &arr, int first, int mid, int last) //Carrano
{
	if (arr[first] > arr[mid])
		swap(arr[first], arr[mid]);

	if (arr[mid] > arr[last])
		swap(arr[mid], arr[last]);

	if (arr[first] > arr[mid])
		swap(arr[first], arr[mid]);

}

void QuickSort(vector<int> &arr, int left, int right) //algolist.net/Algorithms/Sorting/Quicksort
{
	int i = left, j = right;
	
	int mid = left + (right - left) / 2;
	SortFirstMidLast(arr, left, mid, right);//improved on algolist

	int pivot = arr[mid];//improved on algolist

	/* partition */
	while (i <= j) 
	{
		while (arr[i] < pivot)
			i++;
		
		while (arr[j] > pivot)
			j--;
		
		if (i <= j) 
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		QuickSort(arr, left, j);
	if (i < right)
		QuickSort(arr, i, right);
	
}

void Merge(vector<int> &arr, int first, int mid, int last) //Carrano
{
	vector<int> temp(arr.size());

	int first1 = first;
	int last1 = mid;

	int first2 = mid + 1;
	int last2 = last;

	int index = first1;

	while ((first1 <= last1) && (first2 <= last2))
	{
		if (arr[first1] <= arr[first2])
		{
			temp[index] = arr[first1];
			first1++;
		}

		else
		{
			temp[index] = arr[first2];
			first2++;
		}

		index++;
	}

	while (first1 <= last1)
	{
		temp[index] = arr[first1];
		first1++;
		index++;
	}

	while (first2 <= last2)
	{
		temp[index] = arr[first2];
		first2++;
		index++;
	}

	for (index = first; index <= last; index++)
	{
		arr[index] = temp[index];
	}

}

void MergeSort(vector<int> &arr, int first, int last) //Carrano
{
	if (first < last)
	{
		int mid = first + (last - first) / 2;

		MergeSort(arr, first, mid);
		MergeSort(arr, mid + 1, last);

		Merge(arr, first, mid, last);
	}
}

void IterativeMerge(vector<int> &arr, int first, int mid, int last, vector<int> &temp) //mathcs.emory.edu/
{
	int i, j, k;

	i = first;     // Re-adjust the indices
	j = mid;
	k = first;

	while (i < mid || j < last)
	{
		if (i < mid && j < last)
		{  // Both arrays have elements
			if (arr[i] < arr[j])
				temp[k++] = arr[i++];
			else
				temp[k++] = arr[j++];
		}
		else if (i == mid)
			temp[k++] = arr[j++]; // first half is empty
		else if (j == last)
			temp[k++] = arr[i++]; // second half is empty
	}

	//improved on emory -- explicit copy back to original array never happens in this function
}

void IterativeMergeSort(vector<int> &arr, int first, int last) //mathcs.emory.edu/ -- improved
{
	int size = last + 1;
	vector<int> temp(size);
	bool flag = false; //flag to toggle Merge calls

	for (int width = 1; width < size; width = 2 * width)
	{
		for (int i = 0; i < size; i += 2 * width)
		{
			int left, mid, right;

			left = i;
			mid = min(i + width, size);
			right = min(i + 2 * width, size);

			if (!flag) //improved on emory -- alternates between original array and temp
			{
				IterativeMerge(arr, left, mid, right, temp);
				
			}
			else
			{
				IterativeMerge(temp, left, mid, right, arr);				
			}
		}
		if (!flag)
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	}
	
	if (flag) //copy temp back to original only once if necessary
	{
		for (int i = first; i < size; i++)
		{
			arr[i] = temp[i];
		}
	}
}

// array initialization with random numbers
void InitArray(vector<int> &array, int randMax)
{
	int size = array.size();
	for (int i = 0; i < size;)
	{
		int tmp = (randMax == -1) ? rand() : rand() % randMax;
		bool hit = false;
		for (int j = 0; j < i; j++)
		{
			if (array[j] == tmp)
			{
				hit = true;
				break;
			}
		}
		if (hit)
		{
			continue;
		}
		array[i] = tmp;
		i++;
	}
}

// Function to Print Array   
void PrinArray(const vector<int> &array, string name)
{
	int size = array.size();
	for (int i = 0; i < size; i++)
		cout << name << "[" << i << "] = " << array[i] << endl;
}