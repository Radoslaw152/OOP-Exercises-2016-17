#include <iostream>

template<typename T>
void Merge(T* arr, int begin, int middle, int end)
{
	int sizeA = middle - begin + 1;
	int sizeB = end - middle;
	T* leftArr = new T[sizeA];
	T* rightArr = new T[sizeB];
	for (int i = 0; i < sizeA; ++i)
	{
		leftArr[i] = arr[i + begin];
	}
	for (int i = 0; i < sizeB; ++i)
	{
		rightArr[i] = arr[i + middle + 1];
	}
	int i = 0, j = 0, k = begin;
	while (i < sizeA && j < sizeB)
	{
		if (leftArr[i] <= rightArr[j])
		{
			arr[k++] = leftArr[i++];
		}
		else
		{
			arr[k++] = rightArr[j++];
		}
	}
	while (i < sizeA)
	{
		arr[k++] = leftArr[i++];
	}
	while (j < sizeB)
	{
		arr[k++] = rightArr[j++];
	}
	delete[] leftArr;
	delete[] rightArr;
}
template<typename T>
void MergeSort(T* arr, int start, int end)
{
	if (start < end)
	{
		int middle = start + (end - start) / 2;
		MergeSort(arr, start, middle);
		MergeSort(arr, middle + 1, end);
		Merge(arr, start, middle, end);
	}
}
template<typename T>
int Partition(T* arr, int start, int end)
{
	T splitter = arr[end];
	int pivot = start;
	for (int i = start; i < end; ++i)
	{
		if (arr[i] < splitter)
			std::swap(arr[i], arr[pivot++]);
	}
	std::swap(arr[end], arr[pivot]);
	return pivot;
}
template<typename T>
void QuickSort(T* arr, int start, int end)
{
	if (start < end)
	{
		int partition = Partition(arr, start, end);
		QuickSort(arr, start, partition - 1);
		QuickSort(arr, partition + 1, end);
	}
}
template<typename T>
void Heapify(T* arr, int start, int size)
{
	int parent = start;
	int left = 2 * start + 1;
	int right = 2 * start + 2;
	if (left < size && arr[parent] < arr[left])
	{
		parent = left;
	}
	if (right < size && arr[parent] < arr[right])
	{
		parent = right;
	}
	if (parent != start)
	{
		std::swap(arr[parent], arr[start]);
		Heapify(arr, parent, size);
	}
}
template<typename T>
void HeapSort(T* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		Heapify(arr,i, size);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		std::swap(arr[0], arr[i]);
		Heapify(arr, 0, i);
	}
}
int main()
{
	int arr[10] = { 10,-1,15423,2,234,12,232,-213,-2,0 };
	//HeapSort(arr,10);
	//QuickSort(arr,0,9);
	//MergeSort(arr,0,9);
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}