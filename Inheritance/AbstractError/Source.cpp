#include <iostream>
using namespace std;

enum Color
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Orange = 0x0000A5FF,
	White = 0x00FFFFFF,
};


class Shape
{
	Color color;
public:
	Shape(Color color) :color(color) {/*Тело конструктора*/ }
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
};

class Sqaure :public Shape
{
	double side;
public:
	Sqaure(double side, Color color) :Shape(color)
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
};

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::Red);

	/*Square square(5, Color::Red);
	cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
}

/*
Перечисления (enumerations)

Перечисления в языке C++ представляют собой набор целочисленных именнованых констант. Константам неявно присваиваются значения 0, 1, 2 и тд.
Но если явно задать значение хотя бы одной константы, то нумерация продолжится с указанного значения. Явным образом значение можно задавать и каждой константе в перечислении.

Перечисления, так же как классы и структуры, являются пользовательскими типами данных, а переменные этих типов, могут принимать только значения указанные в перечислении
*/