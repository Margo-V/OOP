#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;

namespace Geometry
{
	//typedef unsigned int Color;
	enum Color
	{
		console_black = 0x00,
		console_white = 0xFF, // 15, //0xFFFFFF00,
		console_red = 0xCC, // 12, //0xFF00000,
		console_red_text =  12, //0xFF00000,
		console_green = 0xAA, // 10, //0x00FF0000,
		console_blue = 0x99, // 9, //0x0000FF00
		default_console_color = 0x07, // 7


		black	= 0x00000000, 
		red		= 0x000000FF,
		green	= 0x0000AA00,	
		yellow	= 0x0000FFFF,
		blue	= 0x00FF0000,
		grey	= 0x00555555,
		white	= 0xFFFFFF00,
	};

	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;


		virtual void info()const = 0;
	};


	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		Square(Color color, double side) :Shape(color)//, side(set_side(side))
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}

		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			unsigned int default_color;

			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}

			SetConsoleTextAttribute(hConsole, Color::default_console_color);
		}

		void info()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, Color::console_red_text);
			cout << "\t\t\tКВАДРАТ:\n\n";
			SetConsoleTextAttribute(hConsole, Color::default_console_color);
			
			cout << "Длина стороны:\t" << side << endl;
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			cout << endl;
			draw();
			cout << "\n\n\n";
		}
	};

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 1;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 1;
			this->width = width;
		}

		Rectangle(Color color, double length, double width) :Shape(color)
		{
			set_length(length);
			set_width(width);
		}
		~Rectangle() {}

		double get_area()const
		{
			return length * width;
		}
		double get_perimeter()const
		{
			return (length + width) * 2;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < length; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::default_console_color);
		}
		void info()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, Color::console_red_text);
			cout << "\t\t\tПРЯМОУГОЛЬНИК:\n\n";
			SetConsoleTextAttribute(hConsole, Color::default_console_color);

			cout << "Длина:\t\t" << length << endl;
			cout << "Ширина:\t\t" << width << endl;
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			cout << endl;
			draw();
			cout << "\n\n\n";
		}
	};

	class Circle :public Shape
	{
		UINT start_x = 0;
		UINT start_y = 0;
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 1;
			this->radius = radius;
		}
		void set_start_x(UINT x)
		{
			if (x >= 1000)x = 1000;
			start_x = x;
		}
		void set_start_y(UINT y)
		{
			if (y >= 700)y = 700;
			start_y = y;
		}

		Circle(Color color, double radius, UINT start_x = 0, UINT start_y =0) :Shape(color)
		{
			set_radius(radius);
			set_start_x(start_x);
			set_start_y(start_y);
		}
		~Circle(){}

		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			cout << "Здесь должен быть круг :-)" << endl;
			HWND hwnd = GetConsoleWindow();

			//hwnd = FindWindow(NULL, L"Inheritance");

			//1)Создаем контекст устройства(то, на чем мы будем рисовать)
			HDC hdc = GetDC(hwnd);

			//2)Создаем кисть, которой будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, 5, color); 
			// PS_SOLID -сплошная линия,
			//5- толщина, 
			//color -(обычно задается rgb(100,200, 150)

			//Для заливки круга:
			HBRUSH hBrush = CreateSolidBrush(black);
				
			//3) Выбираем на чем, и чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
		
			//4) Рисуем:
			//Ellipse(hdc, 100, 100, 200, 200);
			/*int x1 = 200;
			int y1 = 200;
			int x2 = x1 + get_diameter();
			int y2 = y1 + get_diameter();
			Ellipse(hdc, x1, y1, x2, y2);*/

			Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			//После того, как кисть не нужна- её нужгл удалить!
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			//После того, как мы все нарисовали?
			//нужно освободить ресурсы, занимаемые контекстом
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, Color::console_red_text);
			cout << "\t\t\tКРУГ:\n\n";
			SetConsoleTextAttribute(hConsole, Color::default_console_color);
			
			cout << "Радиус:\t\t" << radius << endl;
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			cout << endl;
			draw();
		}
	};

	class Triangle :public Shape
	{

	};
}

void main()
{
	setlocale(LC_ALL, "ru");
	//		Set full screen
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 80, 50 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN, &buffer );


	//Shapes
	Geometry::Square square(Geometry::Color::console_red, 5);
	square.info();

	Geometry::Rectangle rect(Geometry::Color::console_green, 4, 8);
	rect.info();

	Geometry::Circle circle(Geometry::Color::yellow, 50, 70, 70);
	circle.info();
}