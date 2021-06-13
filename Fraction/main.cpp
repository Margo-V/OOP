#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;



#define DELIMETR "-------------------------"
#define tab "\t"

using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);

class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель

public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//---------------CONSTRUCTORS---------------
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 0;
		cout << "DefaultConstructor:\t" << tab << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:" <<tab << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->denominator = denominator;
		cout << "Constructor" << tab <<this<< endl;
	}

	Fraction(int integer, int numerator, int denominator)
	{
		this->set_integer(integer);
		this->set_numerator(numerator);
		this->set_denominator(denominator);
		cout << "Constructor" << tab << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << tab << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor" << tab << this << endl;
	}
	//---------------OPERATORS---------------
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignement" << tab << this << endl;
		return *this;
	}

	Fraction& operator*=(const Fraction& other)
	{

		/*this->to_improper();
		other.to_improper();
		
		this->numerator *= other.numerator;
		this->denominator *= other.denominator;
		this->to_proper();
		return *this;*/

		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//---------------INCREMENT/DECREMENT---------------

	Fraction& operator++() //Prefix increment
	{
		integer++;
		return *this;
	}

	Fraction& operator++(int) //Postfix
	{
		Fraction old = *this; //CopyConstructor
		integer++;
		return old;
	}

	//---------------TYPE-CAST operators:---------------
	explicit operator int()const
	{
		return integer;
	}

	operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//---------------METHODS---------------

	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return* this;
	}

	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted()
	{
		to_improper();
		Fraction inverted(denominator, numerator);
		return inverted;
	}

	void print()
	{
		if (integer)cout << integer;
		if (integer && numerator)cout << "(";
		if (numerator)cout << numerator << "/" << denominator;
		if (integer && numerator)cout << ")";
		if (integer == 0 && numerator == 0)cout << 0;
		cout << endl;
	}

	//friend istream& operator>> (istream& is, Fraction& obj);
	//Эта функция имеет set-методы, поэтому данная строка не имеет смысла
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	/*Fraction result;
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denuminator() * right.get_denuminator());
	result.to_proper();
	return result;*/


	return Fraction 
		//Явно вызываем конструктор Fruction и передаем в него параметры
		//Этот конструктор создает временный безымянный объект, который сразу ЖЕ 
		//отправляется return-y
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator/(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();

	Fraction result
	(
		left.get_numerator() * right.get_denuminator(),
		right.get_numerator() * left.get_denuminator()
	);
	return result;*/
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();


}

bool operator!=(Fraction left, Fraction right)
{
	return !(left == right);
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())cout << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())cout << "(";
	if (obj.get_numerator())cout << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator())cout << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)cout << 0;
	return os;
}

istream& operator>> (istream& is, Fraction& obj)
{
	
	int integer, numerator, denominator;
	integer = numerator = denominator = 0;
	/*char str[256];
	char* number[5]{};
	is.getline(str, 256);
	const char* delimiters = "(/)";
	int i = 0;
	for (char* pch = strtok(str, delimiters); pch; pch = strtok(NULL, delimiters), i++)
	//for (number[i] = strtok(str, delimiters); number[i]; number[i++] = strtok(NULL, delimiters), i++)
	{
		//cout << pch << tab;
		number[i] = pch;
	}
	//for (int i = 0; i < 5; i++)cout << number[i] << tab; cout << endl;
	switch (i)
	{
	case 1: integer = atoi(number[0]); break;
	case 2: 
		numerator = atoi(number[0]), 
		denominator = atoi(number[1]); break;
	case 3:
		integer = atoi(number[0]);
		numerator = atoi(number[1]);
		denominator = atoi(number[2]);
	}*/
	//is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	return is;
}


//#define CONSTRUCTORS_CHECK
//#define ARITHMITICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK
//#define COMPARISON_OPERATORS_CHECK
//#define OUT_IN
//#define OTHER_2_THIS_CONVERSIONS

void main()
{
	setlocale(LC_ALL, "ru");
#ifdef CONSTRUCTORS_CHECK
	double a = 5; cout << a << endl;
	Fraction A = 5;
	A.print();
	Fraction B(2, 3, 4);
	B.print();
	Fraction C(0, 1, 2);
	C.print();
	Fraction D;
	D.print();
#endif // CONSTRUCTORS_CHECK
#ifdef ARITHMITICAL_OPERATORS_CHECK
	Fraction A(1, 2, 3);
	/*A.to_improper();
	A.print();*/
	Fraction B(19, 5);
	/*B.to_proper();
	B.print();*/

	//Fraction C = A * B;C.print();
	//Fraction D = A / B;D.print();

	//A *= B;
	A /= B;
	A.print();
#endif // ARITHMITICAL_OPERATORS_CHECK

#ifdef INCREMENT_CHECK
	for (double i = .25; i < 10; i++)
	{
		cout << i << tab;
	}
	cout << endl;

	//for (Fraction i(1, 4); i.get_integer() < 10; (++i).print());


	for (Fraction i(1, 4); i.get_integer() < 10; i++)
	{
		cout << i << endl;
	}
#endif // INCREMENT_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(1, 2);
	Fraction B(5, 11);
	cout << (A == B) << endl;
	cout << (A != B) << endl;
#endif // COMPARISON_OPERATORS_CHECK

#ifdef OUT_IN
	Fraction A;
	cout << "Введите целую часть, числитель и знаменатель через запятую" << endl;
	cin >> A;
	cout << A << endl;
#endif // OUT_IN

#ifdef OTHER_2_THIS_CONVERSIONS
	int a = 2;
	//Fraction A = a;
	Fraction A(a); //explicit constructor можно вызвать только так,
					//его невозможно вызвать оператором =, так как обычный конструктор с одним параметром
	cout << A << endl;
	cout << "\n=============================\n" << endl;
	Fraction B; //default construction
	cout << DELIMETR << endl;
	B = (Fraction)5;
	cout << DELIMETR << endl;
	cout << B << endl;
	cout << "\n=============================\n" << endl;
#endif // OTHER_2_THIS_CONVERSIONS

	Fraction A(2, 3, 4);
	cout << A << endl;
	int a = (int)A;
	cout << "a = " << a << endl;
	double b = A;
	cout << "b = " << b << endl;
}