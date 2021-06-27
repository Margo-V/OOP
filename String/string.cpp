#include "String.h"


////////////////////////////////////////////////////////////////////
//////////		 CLASS DEFINITION (����������� ������)		////////

unsigned int String::get_size()const
{
	return size;
}

const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//				Constructors
String::String(unsigned int size) :size(size), str(new char[size] {})
{
	cout << "Size_DefConstructor:\t" << this << endl;
}

String::String(const char str[]) : String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}

String::String(const String& other) :String(other.str)
{
	//this->size = other.size;
	//this->str = other.str; - Shallow copy(�������������) //������ ��� ������ � �����������!
	//this->str = new char[size] {};
	//for (int i = 0; i < size; i++)
	//{
	//	this->str[i] = other.str[i];	//���������(����������) �����������
	//									//Deep copy
	//}
	cout << "CopyConstructor:" << this << endl;
}
String::String(String&& other)
{
	//MoveConstructor ������ �������� ���, ��� �� ������ �������� CopyConstructor
	//�� ����, CopyConstructor ������ ��������� deep copy, �
	//MoveConstructor - shallow copy, 
	//�� ���� ���������� ������ ����� �� ��� ���������� ������
	//MoveConstructor �� ������ �������� ������������ ������, 
	//�� ����� ������ ���������� ���������� ������� 
	//� �������� � ������������ �������!!!
	//��� ���� ��������� ������ ������ �������� ������ � ������ ��������
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
	cout << "MoveConstructor:" << this << endl;
}

String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t" << this << endl;
}

//				Operators:
String& String::operator=(const String& other) //CopyAssignement
{
	//0) ���������, �� �������� �� this � other ����� � ��� �� ��������:
	if (this == &other)return*this;
	//1) ������� ������ �������� �������
	delete[] this->str;
	//2) ��������� �����������:
	this->size = other.size;
	//this->str = other.str; - Shallow copy(�������������) //������ ��� ������ � �����������!
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)
	{
		this->str[i] = other.str[i];
	}
	cout << "CopyAssignment\t" << this << endl;
	return *this;
}
String& String::operator=(String&& other)
{
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
	cout << "MoveAssignement:" << this << endl;
	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}
const char& String::operator[](unsigned int i)const
{
	return str[i];
}
char& String::operator[](unsigned int i)
{
	return str[i];
}

//				Methods

void String::print()const
{
	cout << "Size: " << size << endl;
	cout << "Str: " << str << endl;
}



String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);// Size Constructor
	//cat-��������� ������, �� ���������� ������ � �������� ������� operator+
	for (int i = 0; i < left.get_size(); i++)
	{
		//cat.get_str()[i] = left.get_str()[i];
		cat[i] = left[i];
	}
	for (int i = 0; i < right.get_size(); i++)
	{
		//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		cat[i + left.get_size() - 1] = right[i];
	}
	return cat;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

std::istream& operator>>(std::istream& is, const String& obj)
{
	return is >> obj.get_str();
}

//////////		 CLASS DEFINITION END (����� ����������� ������)		////////
///////////////////////////////////////////////////////////////////////////////
