#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color	//Enumerations
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF,
		White = 0x00FFFFFF,
		SomeColor
	};

#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color
	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 512;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int filter_size(int size)const
		{
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const
		{
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();

			//2) Получаем контекст устройства (DC - Device Context) для окна консоли:
			HDC hdc = GetDC(hwnd);	//DC - это то, на чем мы будем рисовать

			//3) Создадим инструменты, которыми мы будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//Карандаш (Pen) рисует контур фигуры.
			HBRUSH hBrush = CreateSolidBrush(color);	//Кисть (Brush) отсует заливку фигуры.

			//4) Выьерим созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) После того, как все необходимые инструменты созданы и выбраны, можно рисовать:
			::DrawFunction(hdc, start_x, start_y, start_x + width, start_y + height);

			//6) hdc, hPen и hBrush занимают ресурсы, а ресурсы нужно освобождать:

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return 4 * side;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			cout << endl;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();

			//2) Получаем контекст устройства (DC - Device Context) для окна консоли:
			HDC hdc = GetDC(hwnd);	//DC - это то, на чем мы будем рисовать

			//3) Создадим инструменты, которыми мы будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//Карандаш (Pen) рисует контур фигуры.
			HBRUSH hBrush = CreateSolidBrush(color);	//Кисть (Brush) отсует заливку фигуры.

			//4) Выьерим созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) После того, как все необходимые инструменты созданы и выбраны, можно рисовать:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			//6) hdc, hPen и hBrush занимают ресурсы, а ресурсы нужно освобождать:

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << "x" << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};

	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		//Равносторонний
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return 3 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + side, start_y + get_height() },
				{ start_x + side/2, start_y }
			};
			::Polygon(hdc, vertices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	cout << hex << Geometry::Color::SomeColor << endl;
	//Shape shape(Color::Red);

	Geometry::Square square(5, 100, 100, 1, Geometry::Color::Red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата:" << square.get_perimeter() << endl;
	square.draw();
	cout << "\n-------------------------\n" << endl;*/
	square.info();

	Geometry::Rectangle rect(150, 100, 150, 100, 2, Geometry::Color::Orange);
	rect.info();

	Geometry::Circle circle(50, 800, 200, 1, Geometry::Color::Yellow);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(50, 550, 350, 48, Geometry::Color::Green);
	e_triangle.info();

	while (true)
	{
		square.draw();
		rect.draw();
	}
}