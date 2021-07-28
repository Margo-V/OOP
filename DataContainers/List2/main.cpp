#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	size_t size;

	class BaseConstIterator
	{
	protected:
		Element* Temp;
	public:
		BaseConstIterator(Element* Temp);
		~BaseConstIterator();
		//		Operators:
		bool operator==(const BaseConstIterator& other)const;
		bool operator!=(const BaseConstIterator& other)const;

		const int& operator*()const;
	};

public:
	class ConstIterator :public BaseConstIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	
	};
	class ConstReverseConstIterator: public BaseConstIterator
	{
	public:
		ConstReverseConstIterator(Element* Temp = nullptr);

		~ConstReverseConstIterator();

		ConstReverseConstIterator& operator++();
		ConstReverseConstIterator operator--();
		ConstReverseConstIterator operator++(int);
		ConstReverseConstIterator operator--(int);
		
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();

		int& operator*();
	};
	class ReverseIterator :public ConstReverseConstIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		int& operator*();
	};


	Iterator begin(); 
	ConstIterator cbegin()const;
	Iterator end();
	ConstIterator cend()const;
	

	ReverseIterator rbegin();
	ConstReverseConstIterator crbegin()const;
	ReverseIterator rend();
	ConstReverseConstIterator crend()const;
	

	size_t get_size()const;
	List();


	explicit List(size_t size, int value = int());


	List(const std::initializer_list<int>& il);
	List(const List& other);
	List(List&& other);
	~List();

	//			Operators:
	int& operator[](size_t index);

	//			Adding elements:
	void push_front(int Data);
	void push_back(int Data);
	void insert(size_t index, int Data);

	//			Removing elements:
	void pop_front(); 
	void pop_back();
	
	//			Methods:
	void print()const;
	void reverse_print()const;
};

List::Element::Element(int Data, List::Element* pNext, List::Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor\t" << this << endl;
#endif // DEBUG

}
List::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}

List::BaseConstIterator::BaseConstIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG

}
List::BaseConstIterator::~BaseConstIterator()
{
#ifdef DEBUG
	cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG

}
//		Operators:
bool List::BaseConstIterator::operator==(const BaseConstIterator& other)const
{
	return this->Temp == other.Temp;
}
bool List::BaseConstIterator::operator!=(const BaseConstIterator& other)const
{
	return this->Temp != other.Temp;
}
const int& List::BaseConstIterator::operator*()const
{
	return Temp->Data;
}


List::ConstIterator List::cbegin()const
{
	return Head;
}
List::ConstIterator List::cend()const
{
	return nullptr;
}
List::Iterator List::begin()
{
	return Head;
}
List::Iterator List::end()
{
	return nullptr;
}


List::ConstIterator::ConstIterator(Element* Temp) :BaseConstIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

}
List::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

}
List::ConstIterator& List::ConstIterator::operator++()	//Prefix increment
{
	Temp = Temp->pNext;
	return *this;
}
List::ConstIterator List::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	Temp = Temp->pNext;
	return old;
}
List::ConstIterator& List::ConstIterator::operator--()
{
	Temp = Temp->pPrev;
	return *this;
}
List::ConstIterator List::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}


//CONSTREVERSECONSTITERATOR
List::ConstReverseConstIterator::ConstReverseConstIterator(Element* Temp) :BaseConstIterator(Temp)
{}
List::ConstReverseConstIterator::~ConstReverseConstIterator()
{
#ifdef DEBUG
	cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
}
List::ConstReverseConstIterator& List::ConstReverseConstIterator::operator++()
{
	Temp = Temp->pPrev;
	return *this;
}
List::ConstReverseConstIterator List::ConstReverseConstIterator::operator--()
{
	Temp = Temp->pNext;
	return *this;
}
List::ConstReverseConstIterator List::ConstReverseConstIterator::operator++(int)
{
	ConstReverseConstIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}
List::ConstReverseConstIterator List::ConstReverseConstIterator::operator--(int)
{
	ConstReverseConstIterator old = *this;
	Temp = Temp->pNext;
	return old;
}

//		ITERATOR

List::Iterator::Iterator(Element* Temp): ConstIterator(Temp){}
List::Iterator::~Iterator() {}

int& List::Iterator::operator*()
{
	return Temp->Data;
}

//		ReverseIterator
List::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseConstIterator(Temp) {}
List::ReverseIterator::~ReverseIterator() {}
int& List::ReverseIterator::operator*()
{
	return Temp->Data;
}

///////////////////////////////////////////////////
////////     List member Functions	     //////////
///////////////////////////////////////////////////

List::ReverseIterator List::rbegin()
{
	return Tail;
}
List::ConstReverseConstIterator List::crbegin()const
{
	return Tail;
}
List::ReverseIterator List::rend()
{
	return nullptr;
}
List::ConstReverseConstIterator List::crend()const
{
	return nullptr;
}

size_t List::get_size()const
{
	return size;
}

List::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

}
List::List(size_t size, int value) :List()
{
	while (size--)push_back(value);
}
List::List(const std::initializer_list<int>& il) :List()
{
	for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
List::List(const List& other) :List()
{
	for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
	{
		push_back(*it);
		cout << "LCopyConstructor:\t" << this << endl;
	}
}
List::List(List&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "LMoveConstructor:\t" << this << endl;
}
List::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//			Operators:
int& List::operator[](size_t index)
{
	if (index >= size)throw std::exception("Error out of range"); //Выход за пределы диапозона
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; i++)
			Temp = Temp->pPrev;
	}
	return Temp->Data;
}

//			Adding elements:
void List::push_front(int Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Element* New = new Element(Data);
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
	size++;
}
void List::push_back(int Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Element* New = new Element(Data);
	New->pPrev = Tail;
	Tail->pNext = New;
	Tail = New;
	size++;
}
void List::insert(size_t index, int Data)
{
	if (index > size)return;
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);

	//1) Доходим до позиции, на которую нужно вставить элемент:
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - 1; i++)Temp = Temp->pPrev;
	}
	//2) Создаем элемент и включаем его в список:
	Element* New = new Element(Data);
	New->pPrev = Temp->pPrev;
	New->pNext = Temp;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}

//			Removing elements:
void List::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	//1) Исключаем элемент из списка:
	Head = Head->pNext;
	//2) Удаляем элемент из памяти:
	delete Head->pPrev;
	//3) "Забываем" об удаляемом элементе
	Head->pPrev = nullptr;
	size--;
}
void List::pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		size--;
		return;
	}
	//1) Исключаем элемент из списка:
	Tail = Tail->pPrev;
	//2) Удаляем исключенный элемент из памяти:
	delete Tail->pNext;
	//3)"Затираем" адрес удаленного элемента
	Tail->pNext = nullptr;
	size--;
}

//			Methods:
void List::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << "Head: " << Head << endl;
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<
			Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
}
void List::reverse_print()const
{
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<
			Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
}



List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	
	return cat;
}

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