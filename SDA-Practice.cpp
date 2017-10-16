#include <iostream>
template<typename T>
int BinarySearch(T* arr, int size, T key)
{
	if (arr[size / 2] != key && size == 0) // 0(1)
		return -1;// 0(1)
	if (arr[size / 2] == key) // 0(1)
		return size / 2;// 0(1)
	if (size != 0 && arr[size - 1] == key)// 0(1)
		return size - 1;// 0(1)
	else if (arr[size / 2] < key) // 0(1)
	{
		int result = BinarySearch(arr + size / 2, size / 2, key); //T(n) = 1 + T(n/2) == 0(logn)
		return (result == -1) ? -1 : result + size / 2; //0(1)
	}
	else if (arr[size / 2] > key)//0(1)
		return BinarySearch(arr, size / 2, key);//T(n) = 1 + T(n/2) == 0(logn)

}
template<typename T>
void InsertionSort(T* arr, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int j = 0;
		while (i - j > -1 && arr[i - j] > arr[i + 1 - j])
		{
			std::swap(arr[i - j], arr[i + 1 - j]);
			j++;
		}
	}
}
int main()
{
	int arr[] = { 1,11,12,4,5,333,10 };
	InsertionSort(arr, 7);
	for (int i = 0; i < 7; ++i)
		std::cout << arr[i] << std::endl;
	return 0;
}