#include<iostream>
using namespace std;

#define delimiter "\n--------------------------------------\n"

//virtual type name(parameters)modifiers = 0;

class Vehicle
{
	//Абстрактный класс
	//Абстрактный пацан
	int speed;
public:
	virtual void move() = 0;	//Чисто-виртуальный метод. Именно он и делает класс абстрактным.
	//Класс становится абстрактным, если в нем объявить хотябы один чисто-виртуальный метод.
};

class LandVehicle :public Vehicle{};//Абстрактный класс
	//Абстрактный пацан
class AirVehicle :public Vehicle
{
	int altitude;
public:
	virtual void top_up() = 0;
	virtual void landing() = 0;
};

class Car:public LandVehicle
{
	//Конкретный класс:
	//Конкретный пацан:
public:
	void move()override
	{
		cout << "Машина едет по земле на колесах" << endl;
	}
};
class Bicycle :public LandVehicle
{
public:
	void move()override
	{
		cout << "Это траспортное средство приводится в движение мускульной силой" << endl;
	}
};

class Helicopter:public AirVehicle
{
public:
	void move()override
	{
		cout << "Перемещается на винтах" << endl;
	}
	void top_up()override
	{
		cout << "Взлетает с места, не требуя разгона" << endl;
	}
	void landing()override
	{
		cout << "Приземляется на любую ровную поверхность достаточной площади" << endl;
	}
};
class Plane :public AirVehicle
{
public:
	void top_up()override
	{
		cout << "Для взлета нужно хорошо разогнаться, поэтому нужна взлетная полоса" << endl;
	}
	void landing()override
	{
		cout << "Для посадки тоже нужна ВПП" << endl;
	}
	void move()override
	{
		cout << "Летим очень быстро..." << endl;
	}
};

void main()
{
	cout << sizeof(long long) << endl;
	cout << ULLONG_MAX << endl;
	setlocale(LC_ALL, "");
	//Vehicle vehicle;	//E0322, C2259: Невозможно создать экземпляр абстрактного класса.
	//GroundVehicle gv;
	Car bmw;
	bmw.move();
	cout << delimiter << endl;

	Bicycle bike;
	bike.move();
	cout << delimiter << endl;

	//AirVehicle av;

	Helicopter black_hawk;
	black_hawk.top_up();
	black_hawk.move();
	black_hawk.landing();
	cout << delimiter << endl;

	Plane boeing747;
	boeing747.top_up();
	boeing747.move();
	boeing747.landing();
	cout << delimiter << endl;
}