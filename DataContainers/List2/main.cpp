#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

//Class<type> obj;

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
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
		friend class List<T>;
	}*Head, * Tail;
	size_t size;

	class BaseConstIterator
	{
	protected:
		Element* Temp;
	public:
		BaseConstIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~BaseConstIterator()
		{
#ifdef DEBUG
			cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG

		}
		//		Operators:
		bool operator==(const BaseConstIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseConstIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*()const
		{
			return Temp->Data;
		}
		
	};

public:
	class ConstIterator :public BaseConstIterator
	{
	public:
		ConstIterator(Element* Temp=nullptr):BaseConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator() 
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator++()	//Prefix increment
		{
			BaseConstIterator::Temp = BaseConstIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			BaseConstIterator::Temp = BaseConstIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			BaseConstIterator::Temp = BaseConstIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			BaseConstIterator::Temp = BaseConstIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseConstIterator: public BaseConstIterator
	{
	public:
		ConstReverseConstIterator(Element* Temp = nullptr):BaseConstIterator(Temp)
		{}

		~ConstReverseConstIterator()
		{
#ifdef DEBUG
			cout << "RIDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstReverseConstIterator& operator++()
		{
			BaseConstIterator::Temp = BaseConstIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseConstIterator operator--()
		{
			BaseConstIterator::Temp = BaseConstIterator::Temp->pNext;
			return *this;
		}
		ConstReverseConstIterator operator++(int)
		{
			ConstReverseConstIterator old = *this;
			BaseConstIterator::Temp = BaseConstIterator::Temp->pPrev;
			return old;
		}
		ConstReverseConstIterator operator--(int)
		{
			ConstReverseConstIterator old = *this;
			BaseConstIterator::Temp = BaseConstIterator::Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		T& operator*()
		{
			return BaseConstIterator::Temp->Data;
		}
	};
	class ReverseIterator:public ConstReverseConstIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseConstIterator(Temp){}
		~ReverseIterator() {}
		T& operator*()
		{
			return BaseConstIterator::Temp->Data;
		}
	};
	
	Iterator begin()
	{
		return Head;
	}
	const ConstIterator cbegin()const
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	const ConstIterator cend()const
	{
		return nullptr;
	}
	

	ReverseIterator rbegin()
	{
		return Tail;
	}
	const ConstReverseConstIterator crbegin()const
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	const ConstReverseConstIterator crend()const
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
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	explicit List(size_t size, T value= T()) :List()
	{
		while (size--)push_back(value);
	}
	List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
	{
		for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
		{
			push_back(*it);
			cout << "LCopyConstructor:\t" << this << endl;
		}
	}
	List(List<T>&& other)
	{
		this->size = other.size;
		this->Head = other.Head;
		this->Tail = other.Tail;
		other.Head = other.Tail = nullptr;
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	T& operator[](size_t index)
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
	void push_front(T Data)
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
	void push_back(T Data)
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
	void insert(size_t index, T Data)
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

template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	
	return cat;
}

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SYBSCRIPT
//#define ConstIteratorS_CHECK
//#define HARDCORE
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK
//#define OPERATOR_PLUS

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
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	list3.print();
	for (int i : list1)
		cout << i << tab;
	cout << endl;
	for (int i : list2)
		cout << i << tab;
	cout << endl;

#endif // OPERATOR_PLUS


	List<std::string> list1 = { "Хорошо ", "живет ", "на ", "свете ", "Винни-Пух" };
	list1.print();
	List<std::string> list2 = { "С ", "детства ", "c ", "рифмой ", "я ", "дружу." };
	list2.print();
	List<std::string> list3 = list1 + list2;
	for (std::string i : list3)cout << i << tab;
	cout << endl;

}