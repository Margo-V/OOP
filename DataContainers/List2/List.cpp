#include "List.h"


///////////////////////////////////////////////////
////////    CLASS DEFINITION	     //////////
///////////////////////////////////////////////////

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
List::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}
List::Iterator::~Iterator() {}
int& List::Iterator::operator*()
{
	return Temp->Data;
}

//		REVERSEITERATOR
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
List::List(const std::initializer_list<int>& il) : List()
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
