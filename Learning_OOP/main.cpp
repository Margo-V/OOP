#include <iostream>

using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------\n"
#define HELLO(arg) "Hello "#arg


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

	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/


	Point(double x=0, double y=0)
	{
		//Этот конструктор с параметрами является также конструктором по учолчанию,
		//поскольку его можно вызвать без параметров, тогда оба его параметра примут
		//значение по умолчанию, т.е. 0
		this->x = x;
		this->y = y;
		cout << "Constructor:" << this << endl;
	}

	Point(const Point& other)
	{
		//Принимает другой существующий объект по константной ссылке,
		//other - это просто имя принимаемого параметра( имя другого объекта)
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}


	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignement:\t" << this << endl;
		return *this;
	}
	/*Point operator+(const Point& other)const
	{
		Point result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;
		cout << "Operator+:\t" << this << endl;
		return result;
	}*/

	Point& operator++() //Prefix Increment
	{
		this->x++;
		this->y++;
		cout << "Prefix Increment:\t" << this << endl;
		return *this;
	}
	Point operator++(int) // Postfix increment
	{
		Point old = *this;
		this->y++;
		this->x++;
		cout << "Suffix Increment:\t" << endl;
		return old;
	}

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

	double distance(const Point& other)const
	{
		this;//Эта точка, в которой мы сейчас находимся
		other;//Та точка, до которой нужно вычислить расстояние
		double x_distance = this->x  - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;
	}

};


double distance_function(double x, double y);
double distance(const Point& A, const Point& B);
Point operator+(const Point& left, const Point& right);

//#define STRUCT
//#define CONSTRUCTORS

#define CONSTRUCTOR_S
//#define DISTANCE_AND_CONSTRUCTORS
//#define ASSIGNEMENT_CHECK

void main()
{
	setlocale(LC_ALL, "ru");
	int a, b;
	//int c = a + b;
	Point A(2.3, 4.5);
	Point B(2.7, 3.14);
	cout << delimiter << endl;
	Point C = A + B;
	cout << delimiter << endl;
	C.Print();
	++C;
	C.Print();
	C++;
	C.Print();

#ifdef DISTANCE_AND_CONSTRUCTORS
	Point A(2.3, 4.5);
	Point D(6.7, 8.3);
	cout << delimiter << endl;
	//A-this, D - other
	cout << "Расстояние от точки A до точки D: " << A.distance(D) << endl;
	//D-this, A - other
	cout << "Расстояние от точки D до точки A: " << D.distance(A) << endl;

	cout << "\n\nРасстояние между точками A и D: " << distance(A, D) << endl;
	cout << "Расстояние между точками D и A: " << distance(D, A) << endl;
	cout << delimiter << endl;

	Point AA(2.3, 4.5);		//Constructor
	AA.set_x(2);
	AA.set_y(3);
	cout << sizeof(A) << endl;
	cout << AA.get_x() << tab << AA.get_y() << endl;

	Point B;		//DefaultConstructor
	B.Print();

	Point C = AA;	//CopyConstructor  

	B = D;			//CopyAssignement
	cout << delimiter << endl;

	Point E = A;	//CopyConstructor
	Point F;		//DefaultConstructor
	F = D;			// CopyAssignement
	cout << delimiter << endl;
#endif // DISTANCE_AND_CONSTRUCTORS

#ifdef ASSIGNEMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << tab << b << tab << c << endl;
	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2.3, 4.5);
	//Point(2.3, 4.5)-явный вызов конструктора
	// Временный безымянный объект, который существует 
	// только в пределах 
	cout << delimiter << endl;								// этого выражения
	//l-value = r-value;
	//	Point = void
	A.Print();
	B.Print();
	C.Print();

#endif // ASSIGNEMENT_CHECK
	//cout << HELLO(guy) << endl;

#ifdef CONSTRUCTORS
	double x, y;
	Point D;
	cout << "\nВведите значение точки X:" << tab; cin >> x;
	cout << "Введите значение точки Y" << tab; cin >> y;
	cout << "Расстояние от X до Y:" << tab << D.distance_method(x, y) << endl;


	cout << "\n\nВведите значение точки X:" << tab; cin >> x;
	cout << "Введите значение точки Y:" << tab; cin >> y;
	cout << "Расстояние от X до Y:" << tab << distance_function(x, y) << endl;
#endif // CONSTRUCTORS
		

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

double distance(const Point& A, Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();

	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	cout << "Global Plus" << endl;
	return result;
}