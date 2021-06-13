#include <iostream>

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
	Fraction(int integer)
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


//#define CONSTRUCTORS_CHECK
//#define ARITHMITICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK

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

	Fraction A(1, 2);
	Fraction B(5, 11);
	cout << (A == B) << endl;
	cout << (A != B) << endl;
}