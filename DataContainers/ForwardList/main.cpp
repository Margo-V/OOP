#include <iostream>

using namespace std;

#define tab "\t"


class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};


class ForwardList
{
	Element* Head;
public:
	ForwardList()	//Default constructor - создает пустой список.
	{
		this->Head = nullptr; //Если голова указывает на 0, то список пуст.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//			Adding elements
	void push_front(int Data)
	{
		//Добавление элемента в начало списка:
		//1) Создаем элемент:
		Element* New = new Element(Data);

		//2) Прикрепляем новый элемент к списку:
		New->pNext = Head;

		//3) Адрес нового элемента помещаем в голову, 
		Head = New;
		//после чего новый элемент явдяется начальным элементом списка
	}


	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			//если список пуст, вызываем метод,
			//который умеет добавлять метод в пустой список
			return push_front(Data);
		}

		//1) Создать новый элемент:
		//Element* New = new Element(Data);

		//2) Дойти до конца списка (до последнего элемента):(циклом и итератор)
		//Объявим итератор
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext; //Переходим на следующий элемент

		//3) В pNext последнего элемента добавить адрес нового элемента
		Temp->pNext = new Element(Data);
	}



	//			Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp-это итератор
		//Итератор-это указатель, при помощи которого 
		//можно получить доступ к элементам структуры данных

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "ru");
	int n; 
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
}