#include <iostream>

using namespace std;

#define tab "\t"
#define delimeter "\n------------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	size_t size; //size_tunsigned int
public:
	ForwardList()	//Default constructor - ������� ������ ������.
	{
		this->Head = nullptr; //���� ������ ��������� �� 0, �� ������ ����.
		
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(size_t size):ForwardList()
	{
		while ( size--)push_front(0);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
			
		cout << "LCopyConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:

	ForwardList& operator=(const ForwardList& other)
	{
		//0) ���������, �� �������� �� this � other ����� � ��� �� ��������:
		if (this == &other)return *this; //�������� �� ������ �������
		//1) ������� ������ �������� �������(������� ������)
		while (Head)
			pop_front();
		//2) �������� ��� ������ � ���� ������
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}

	int& operator[](size_t index)
	{
		if (index >= size)
			throw std::exception("Error: Out of range");
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements
	void push_front(int Data)
	{
		//���������� �������� � ������ ������:
		//1) ������� �������:
		//Element* New = new Element(Data);

		//2) ����������� ����� ������� � ������:
		//New->pNext = Head;

		//3) ����� ������ �������� �������� � ������, 
		//Head = New;
		//����� ���� ����� ������� �������� ��������� ��������� ������
		

		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			//���� ������ ����, �������� �����,
			//������� ����� ��������� ����� � ������ ������
			return push_front(Data);
		}

		//1) ������� ����� �������:
		//Element* New = new Element(Data);

		//2) ����� �� ����� ������ (�� ���������� ��������):(������ � ��������)
		//������� ��������
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext; //��������� �� ��������� �������

		//3) � pNext ���������� �������� �������� ����� ������ ��������
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)
			return push_front(Data);

		//1) ������� ����� �������:
		Element* New = new Element(Data);

		//2) ������� �� ��������, ������� ��������� ����� ����������� ���������:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		//3) ��������� ����� ������� � ������
		//Temp-���������� �������, ������������ ���� ��������,
		//�� ����� �������� ����� ������� �������
		//Temp->pNext -��� ������� �� ����� �������� �� ��������� ����� �������
		//Temp->pNext � ��� ����������� �������� 
		//����� �������� �� ���� ������� ������
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//			Removing elements:
	void pop_front()
	{
		//1)���������� ����� ���������� ��������;
		Element* Temp = Head;

		//2)������� Head(������)  �� ��������� ������� ������
		Head = Head->pNext;

		//3) ������� ������� �� ������:
		delete Temp;
		size--;
	}

	void pop_back()
	{
		//1) ������� �� �������������� ��������:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index == 0)return pop_front();
		else
		{
			Element* Temp = this->Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			Element* toDelete = Temp->pNext;
			Temp->pNext = toDelete->pNext;
			delete Temp;
		}
	}

	//			Methods:
	void print()const
	{
		/*Element* Temp = Head;	//Temp-��� ��������
		//��������-��� ���������, ��� ������ �������� 
		//����� �������� ������ � ��������� ��������� ������

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}*/
		//cout << "���������� ��������� ������: " << size << endl;
		//cout << "����� ���������� ��������� ������: " << Element::count << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};


//#define BASE_CHECK		//Almost Done
//#define SIZE_CONSTRUCTOR_AND_SUBSCRIPT
#define COPY_METHODS


//#define INIT_LIST_LIKE_ARRAY

void main()
{
	setlocale(LC_ALL, "ru");
	/**/


#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;

	list.insert(index, value);
	list.print();

	/*ForwardList list2;
	list2.push_back(1024);
	list2.push_back(2048);
	list2.push_back(3072);
	list2.print();
	cout << delimeter;*/
	//list2.erase(2);
	//list2.print();

#endif // BASE_CHECK


#ifdef INIT_LIST_LIKE_ARRAY
	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // INIT_LIST_LIKE_ARRAY

	//-----------------------------------------
#ifdef SIZE_CONSTRUCTOR_AND_SUBSCRIPT
	//ForwardList list(n);	//��������� ������ �� n ���������
	//for (int i = 0; i < list.get_size(); i++)cout << list[i] << tab;
	//for (int i = 0; i < list.get_size(); i++)list[i]=rand()%100;
	//for (int i = 0; i < list.get_size(); i++)cout << list[i]<<tab;
	int n;
	cout << "������� ������ ������: "; cin >> n;

	ForwardList list(n);

	try
	{
		for (int i = 0; i < n; i++)list[i] = rand() % 100;
		for (int i = 0; i < n; i++)cout << list[i] << tab;
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}

#endif // SIZE_CONSTRUCTOR_AND_SUBSCRIPT

#ifdef COPY_METHODS
	ForwardList list;
	list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.push_back(13);
	list.push_back(21);
	cout << "\n\t\t\tlist:\n" << endl;
	list.print();

	ForwardList list2 = list; //CopyConstructor
	cout << "\n\t\t\tlist2:\n" << endl;
	list2.print();


	ForwardList list3;	//Default constructor
	list3 = list2;		//Copy assignment
	cout << "\n\t\t\tlist3:\n" << endl;
	list3.print();

#endif // COPY_METHODS



}