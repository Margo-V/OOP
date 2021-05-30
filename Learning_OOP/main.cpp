#include <iostream>

using namespace std;

#define tab "\t"

// описывает точку на плоскости
class Point 
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//			Constructors:
#ifdef CONSTRUCTORS
	Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}
#endif // CONSTRUCTORS

	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		//cout << "Constructor:\t" << this << endl;
	}
#ifdef CONSTRUCTORS
	Point(const Point& other)
	{
		//Принимает другой существующий объект по константной ссылке,
		//other - это просто имя принимаемого параметра( имя другого объекта)
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}
#endif // CONSTRUCTORS



	//			Methods
	void Print()
	{
		cout << "X = " << x << tab << "Y = " << y << endl;
	}

	double distance_method(double distance_x, double distance_y )
	{
		this->x = distance_x;
		this->y = distance_y;
		return x < y ? (y - x) : (x - y);
	}

};


double distance_function(double x, double y);

//#define STRUCT
//#define CONSTRUCTORS



void main()
{
	setlocale(LC_ALL, "ru");

#ifdef CONSTRUCTORS
	Point A(2.3, 4.5);		//Constructor
	A.set_x(2);
	A.set_y(3);
	cout << sizeof(A) << endl;
	cout << A.get_x() << tab << A.get_y() << endl;

	Point B;				//DefaultConstructor
	B.Print();

	Point C = A;		//CopyConstructor  
#endif // CONSTRUCTORS

	double x, y;
	Point D;
	cout << "\nВведите значение точки X:" << tab; cin >> x;
	cout << "Введите значение точки Y" << tab; cin >> y;
	cout << "Расстояние от X до Y:"<< tab << D.distance_method(x, y) << endl;


	cout << "\n\nВведите значение точки X:" << tab; cin >> x;
	cout << "Введите значение точки Y:" << tab; cin >> y;
	cout << "Расстояние от X до Y:"<<tab << distance_function(x, y) << endl;

#ifdef STRUCT
	int a;		// Объявление(создание) переменной 'a' типа 'int'
	Point A;	//Объявление (создание) переменной типа 'Point'
				// Создание объекта структуры Point
				// Объявление объекта структуры Point
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;
	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
#endif // STRUCT


}

double distance_function(double x, double y)
{

	return x<y ? (y -x) : (x-y) ;
}