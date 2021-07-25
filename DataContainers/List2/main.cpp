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
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head, * Tail;
	size_t size;

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "BITConstructor:\t" << this << endl;
		}
		~BaseIterator()
		{
			cout << "BITDestructor:\t" << this << endl;
		}
		//		Operators:
		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

public:
	class Iterator :public BaseIterator
	{

	public:
		Iterator(Element* Temp=nullptr):BaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator() 
		{
			cout << "ItDestructor:\t" <<this << endl;
		}
		Iterator& operator++()	//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		/*bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}*/
	};


	class ReverseIterator: public BaseIterator
	{

	public:
		ReverseIterator(Element* Temp = nullptr):Temp(Temp){}
		
		

		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		/*bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}*/
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	size_t get_size()const
	{
		return size;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(size_t size, int value= int()) :List()
	{
		while (size--)push_back(value);
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	int& operator[](size_t index)
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
	void push_front(int Data)
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
	void push_back(int Data)
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
	void insert(size_t index, int Data)
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
	void pop_front()
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
	void pop_back()
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
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << "Head: " << Head << endl;
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<
				Temp->pNext << endl;
			cout << "Количество элементов списка: " << size << endl;
		}
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab <<
				Temp->pNext << endl;
			cout << "Количество элементов списка: " << size << endl;
		}
	}
};

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SYBSCRIPT
//#define ITERATORS_CHECK
#define HARDCORE
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK

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
	/*for (List::Iterator it = list.begin(); it != list.end(); it++)
		cout << *it << tab;
	cout << endl;*/
	/*for (List::Iterator it = list.end(); it != list.begin(); it--)
		cout << *it << tab;
	cout << endl;*/
	
	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)
		cout << *rit << tab;
	cout << endl;
	
#endif // HARDCORE

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();

#endif // ITERATORS_CHECK


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


}