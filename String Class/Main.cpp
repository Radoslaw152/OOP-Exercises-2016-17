#include "String.h"
#include <iostream>

int main()
{
	String arr1("Radoslav");
	arr1.Print();
	String arr2("Mitev");
	arr2.Print();
	arr1.Append(arr2);
	arr1.Print();
	String arr3 = arr1 + arr2;
	arr3.Print();
	arr3 += arr1;
	arr3.Print();
	arr3 += arr2;
	arr3.Print();
	return 0;
}