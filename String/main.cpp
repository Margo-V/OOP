#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------------\n"

////////////////////////////////////////////////////////////////////
/////////////// CLASS DECLARATION (���������� ������) /////////////
class String;
String operator+(const String& left, const String& right);



class String //�������� ������
{
	unsigned int size;  // ������ ������ � ������
	char* str;			// ��������� �� ������ � ������������ ������
public:
	unsigned int get_size()const;
	const char* get_str()const;
	char* get_str();
	//				Constructors
	explicit String(unsigned int size = 80); 

	String(const char str[]);

	String(const String& other);
	String(String&& other);

	~String();

	//				Operators:
	String& operator=(const String& other);
	String& operator=(String&& other);
	String& operator+=(const String& other);
	const char& operator[](unsigned int i)const;
	char& operator[](unsigned int i);

	//				Methods

	void print()const;
};
///////		  CLASS DECLARATION END (����� ���������� ������)	  //////
///////////////////////////////////////////////////////////////////////


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
explicit String::String(unsigned int size = 80) :size(size), str(new char[size] {})
{
	cout << "Size_DefConstructor:\t" << this << endl;
}

String::String(const char str[]) :String(strlen(str) + 1)
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

/*std::istream& operator>>(std::istream& is, const String& obj)
{
	return is >> obj.get_str();
}*/

//////////		 CLASS DEFINITION END (����� ����������� ������)		////////
///////////////////////////////////////////////////////////////////////////////

//#define CONSTRUCTORSCHECK
//#define INPUT_CHECK
#define OPERATOR_PLUS_CHECK
//#define HOW_CAN_WE_CALL_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "ru");
#ifdef CONSTRUCTORSCHECK
	String str;
	str.print();
	String str1 = "Hello";
	str1 = str1;
	str1.print();
	cout << str1 << endl;
	String str2 = str1;//CopyConstructor
	str2.print();
	String str3;
	str3 = str2;	//CopyAssignement(����������� ������������)
	cout << str3 << endl;
#endif // CONSTRUCTORSCHECK

#ifdef INPUT_CHECK
	String str;
	cout << "������� ������:" << tab; cin >> str;
	cout << str << endl;
#endif // INPUT_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimeter << endl;
	//String str3;		//Default Constructor
	//str3 = str1 + str2;	//Move Assignment
	//MoveMethods:MoveConstructor, MoveAssignement
	//cout << str3 << endl;
	str1 += str2;
	cout << str1 << endl;
	cout << delimeter << endl;
	String str3 = str1;
	cout << delimeter << endl;

	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;			//Default constructor
	String str2 = "Hello";	//Single-argument constructor
	String str3 = str2;		//Copy constructor - ������ ��� �� ������� ������
	String str4;
	str4 = str3;			//Copy Assignment(operator=). Copy constructor
							//������� ����������, ��������� ������ str4 ��� ������
	String str5();			//�� Default constructor, ����� ������ �� ��������� ������
							//���������� ������� str5, ������� ������ �� ���������,
							//� ���������� �������� ���� String.
	String str6{};			//����� ����� ������������ �� ���������  
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS


}