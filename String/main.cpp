#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------------\n"

class String;
String operator+(const String& left, const String& right);

class String
{
	unsigned int size;  // Размер строки в байтах
	char* str;			// Указатель на строку в динамической памяти
public:
	unsigned int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	//				Constructors
	explicit String(unsigned int size = 80):size(size), str(new char[size]{})
	{
		//this->size = size;
		//this->str = new char[size] {};
		cout << "Size_DefConstructor:\t" << this << endl;
	}

	String(const char str[]):size(strlen(str)+1), str(new char[size]{})
	{
		//this->size = strlen(str) + 1;
		//this->str = new char[size] {};
		for (int i = 0; str[i]; i++)
		{
			this->str[i] = str[i];
		}
		cout << "Constructor:\t" << this << endl;
	}

	String(const String& other) :size(other.size), str(new char[size] {})
	{
		//this->size = other.size;
		////this->str = other.str; - Shallow copy(поверхностное) //Нельзя так делать с указателями!
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.str[i];	//Побитовое(побайтовое) копирование
											//Deep copy
		}
		cout << "CopyConstructor:" << this << endl;
	}
	String( String&& other):size(other.size), str(other.str)
	{
		//MoveConstructor должен работать так, как не должен работать CopyConstructor
		//то есть, CopyConstructor должен выполнять deep copy, а
		//MoveConstructor - shallow copy, 
		//то есть копировать только адрес на уже выделенную память
		//MoveConstructor не должен выделять ДИНАМИЧЕСКУЮ ПАМЯТЬ, 
		//он берет память временного безымяного объекта 
		//и передает её создаваемому объекту!!!
		//При этом временный объект должен потерять доступ к своему значению
		//this->size = other.size;
		//this->str = other.str;
		other.str = nullptr;
		cout << "MoveConstructor:" << this << endl;
	}

	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t" << this << endl;
	}

	//				Operators:
	String& operator=(const String& other) //CopyAssignement
	{
		//0) Проверить, не является ли this и other одним и тем же объектом:
		if (this == &other)return*this;
		//1) Удаляем старое значение объекта
		delete[] this->str;
		//2) Выполняем копирование:
		this->size = other.size;
		//this->str = other.str; - Shallow copy(поверхностное) //Нельзя так делать с указателями!
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.str[i];
		}
		cout << "CopyAssignment\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		cout << "MoveAssignement:" << this << endl;
		return *this;
	}
	String& operator+=(const String& other)//:size(other.size) 
											//- список-инициализации можно использовать только в конструкторах
	{
		return *this = *this + other;
	}
	const char& operator[](unsigned int i)const 
	{
		return str[i];
	}
	char& operator[](unsigned int i)
	{
		return str[i];
	}

	//				Methods

	void print()const
	{
		cout << "Size: " << size << endl;
		cout << "Str: " << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);// Size Constructor
	//cat-локальный объект, он существует только в пределах функции operator+
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
	str3 = str2;	//CopyAssignement(Конструктор присваивания)
	cout << str3 << endl;
#endif // CONSTRUCTORSCHECK

#ifdef INPUT_CHECK
	String str;
	cout << "Введите строку:" << tab; cin >> str;
	cout << str << endl;
#endif // INPUT_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimeter << endl;
	String str3;		//Default Constructor
	str3 = str1 + str2;	//Move Assignment
	//MoveMethods:MoveConstructor, MoveAssignement
	cout << delimeter << endl;
	cout << str3 << endl;


	str1 += str2;
	cout << str1 << endl;

	String str3 = str1;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;			//Default constructor
	String str2 = "Hello";	//Single-argument constructor
	String str3 = str2;		//Copy constructor - потому что мы создаем объект
	String str4;
	str4 = str3;			//Copy Assignment(operator=). Copy constructor
							//вызвать невозможно, поскольку объект str4 уже создан
	String str5();			//НЕ Default constructor, здесь вообще не создается объект
							//Объявление функции str5, которая ничего не принимает,
							//и возвращает значение типа String.
	String str6{};			//Явный вызов конструктора по умолчанию  
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS


}