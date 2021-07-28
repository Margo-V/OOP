#include "List.h"
//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SYBSCRIPT
//#define ConstIteratorS_CHECK
//#define HARDCORE
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK
#define OPERATOR_PLUS

void main()
{
	setlocale(LC_ALL, "ru");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}

	size_t index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);

	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_SYBSCRIPT
	int n;
	cout << "Введите размер списка: "; cin >> n;

	List list(n);

	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;

	for (int i = 0; i < list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;

	for (int i = list.get_size() - 1; i >= 0; i--)
		cout << list[i] << tab;
	cout << endl;
#endif // SIZE_CONSTRUCTOR_AND_SYBSCRIPT

#ifdef HARDCORE
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab;
	cout << endl;
	/*for (List::ConstIterator it = list.begin(); it != list.end(); it++)
		cout << *it << tab;
	cout << endl;*/
	/*for (List::ConstIterator it = list.end(); it != list.begin(); it--)
		cout << *it << tab;
	cout << endl;*/
	
	for (List::ReverseConstIterator rit = list.rbegin(); rit != list.rend(); rit++)
		cout << *rit << tab;
	cout << endl;
	
#endif // HARDCORE

#ifdef ConstIteratorS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();

#endif // ConstIteratorS_CHECK

#ifdef COPY_CONSTRUCTOR_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();

	List list2 = list;
	list2.print();
	list2.reverse_print();

#endif // COPY_CONSTRUCTOR_CHECK

#ifdef COPY_ASSIGNMENT_CHECK
	List list3;
	list3 = list;
	list3.print();
	list.reverse_print();
#endif // COPY_ASSIGNMENT_CHECK

#ifdef OPERATOR_PLUS
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	list3.print();
	for (int i : list1)
		cout << i << tab;
	cout << endl;
	for (int i : list2)
		cout << i << tab;
	cout << endl;

#endif // OPERATOR_PLUS

}