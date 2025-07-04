#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------------------------------------\n"

class Point
{
	//Создавая структуру или класс мы создаем новый тип данных (пользовательский тип данных)
	//Пользовательские типы являются более сложными, поскольку могу включать в себя множество
	//однотипных или разнотипных значений, которые являются характеристиками и состояниями объектов
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
		//l-value = r-value;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//			Constructors;
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	/*Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "SingleArgumentConstructor:" << this << endl;
		//Конструктор с одним параметром
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;;
	}

	//			Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	Point& operator++()		//Prefix increment
	{
		x++;
		y++;
		return *this;
	}
	Point operator++(int)	//Postfix (Suffix) increment
	{
		Point old = *this;	//Сохраняем старое значение объекта
		x++;
		y++;
		return old;
	}

	//			Methods:
	double distance(const Point& other)const
	{
		//this - эта точка (находим расстояние от этой точки);
		//other - та точка (до указанной точки);
		//this->x *= 100;		//E0137
		//other.x *= 100;	//E0137
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		//sqrt() - Square Root (Квадратный корень)
		return distance;
	}
	void print()const
	{
		cout << this << ": X = " << x << ",\tY = " << y << endl;
	}
};

double distance(const Point& A, const Point& B)
{
	//A.set_x(A.get_x() * 100);
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	return result;
}

bool operator==(const Point& left, const Point& right)
{
	/*
	if (left.get_x() == right.get_x() && left.get_y() == right.get_y())
		return true;
	else
		return false;
	*/

	/*if (condition)
	{
		....;
		code1;
		....;
	}
	else
	{
		....;
		code2;
		....;
	}*/
	return left.get_x() == right.get_x() && left.get_y() == right.get_y();
}
bool operator!=(const Point& left, const Point& right)
{
	return !(left == right);
}

//#define STRUCT_POINT
//#define DISTANCE_CHECK
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a;		//Объявление переменной 'a' типа 'int';
	Point A;	//Объявление переменной 'A' типа 'Point';
				//Создание объекта 'A' структуры 'Point';
				//Создание экземпляра 'A' структуры 'Point';
				//'A' is instance of struct 'Point'
				//Instantiate - создать объект.
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << B.get_x() << "\t" << B.get_y() << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'A' до точки 'B':" << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'B' до точки 'A':" << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'A' и 'B':  " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'B' и 'A':  " << distance(B, A) << endl;
	cout << delimiter << endl;
	cout << sizeof(Point) << endl;
#endif // DISTANCE_CHECK

	/*for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;*/

#ifdef CONSTRUCTORS_CHECK
	Point A;		//Здесь мы просто создаем объект, и для этого неявно вызывается конструктор по умолчанию
	A.print();
	//{
	//	//Point A;
	//	Point B;
	//	cout << "Point B существует" << endl;
	//	B.distance(A);
	//}
	//cout << "Здесь Point B уже НЕ существует" << endl;

	Point B = 5;	//Single-argument constructor - Конструктор с одним параметром
	B.print();

	Point C(7, 8);	//
	C.print();

	Point D = C;	//Copy constructor
	D.print();

	Point E;		//Default constructor
	E = D;			//Assignment operator
	E.print();

#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2, 3);
	//Point(2,3) - здесь мы явно вызываем конструктор, и создаем временный безымянный объект
	cout << delimiter << endl;
	A.print();
	B.print();
	C.print();
#endif // ASSIGNMENT_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Point A(2, 3);
	Point B(7, 8);
	Point C = A + B;
	C.print();

	A = B++;
	A.print();
	B.print();
#endif // ARITHMETICAL_OPERATORS_CHECK

	cout << (Point(2, 3) != Point(7, 8)) << endl;

}

/*
-----------------------------------------------------------
.  - Оператор прямого доступа (Point operator)
-> - Оператор косвенного доступа (Arrow operator)
-----------------------------------------------------------
*/

/*
-----------------------------------------------------------
1. Encapsulation:
	Модификаторы доступа
		private:	закрытые поля, доступны только внутри класса		(member-variables);
		public:		открытые поля, доступны из любого меств программы	(member-function);
		protected:	защищенные поля, доступны только внутри класса
					и его дочерних классов;
	get/set-методы:
	get (взять, получить) - эти методы открывают доступ к переменным членам класса на чтение,
							т.е., позволяют получить значение переменно в классе;
	set (задать, установить)эти методы открывают доступ к переменным членам класса на запись,
							т.е., позволяют завать значения закрытых переменных.
							Кроме того, set-методы обеспечивают фильтрацию данных,
							т.е., предотвращают попадание некорретных значений в переменные члены класса.

2. Inheritance;
3. Polymorphism;
-----------------------------------------------------------
*/

/*
-----------------------------------------------------------
this - это указатель на объект, для которого вызывается метод.
-----------------------------------------------------------
*/

/*
-----------------------------------------------------------
1. Constructor - это метод, который создает объект,
				 а именно, выделяет память под объект,
				 и инициализирует его поля (переменные слены класса);
					- с параметрами;
					- без параметров;
					- по умолчанию - это конструктор, который может быть вызван без параметров;
					- конструктор копирования;
					- конструктор переноса;
2. ~Destructor - это метод, который уничтожает объект по истечении его времени жизни;
3. Assignment operator;
-----------------------------------------------------------
*/

/*
---------------------------------------
				Overloading rules:
1. Перегрузить можно только существующие операторы:
	+	перегружается;
	++	перегружается;
	%	перегружается;
	%%	НЕ перегружается;
2. НЕ все существующие операторы можно перегрузить.
   НЕ перегружается:
	?:	Conditional Ternary Operator;
	::	Оператор разрешения видимости (Scope operator);
	.	Оператор прямого доступа (Point operator);
	.*	Pointer to member selection;
	#	Preprocessor convert to string;
	##	Preprocessor concatenate;
3. Перегруженные операторы сохраняют приоритет;
4. Переопределить поведение операторов над встроенными типами невозможно;
---------------------------------------
	operator@
---------------------------------------
*/