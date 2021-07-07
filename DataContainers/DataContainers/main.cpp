#include <iostream>

using namespace std;
#define tab "\t"

void main()
{
	setlocale(LC_ALL, "ru");
	int arr[] = { 3, 5, 8, 13, 21 };
	cout << arr << endl;

	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr + i << "\t";
	}
	cout << endl;

}