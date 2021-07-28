#pragma once
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

///////////////////////////////////////////////////
////////     CLASS DECLARATION	     //////////
///////////////////////////////////////////////////


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
	class ConstReverseConstIterator : public BaseConstIterator
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
List operator+(const List& left, const List& right);