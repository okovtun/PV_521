//CreationalPatterns/Singleton
#include<iostream>
using namespace std;

class Singleton
{
	int value;
	static Singleton* object;
	Singleton() {}
	Singleton(const Singleton& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;
public:
	int get_value()const
	{
		return value;
	}
	void set_value(int value)
	{
		this->value = value;
	}
	static Singleton* get_instance()
	{
		if (object == nullptr)object = new Singleton();
		return object;
	}
	void info()const
	{
		cout << "Singleton:\t" << this << endl;
		cout << "Object:\t\t" << object << endl;
		cout << "Value:\t\t" << value << endl;
		cout << "\n-----------------------------\n" << endl;
	}
};
Singleton* Singleton::object = nullptr;

void main()
{
	Singleton* obj;
	obj = obj->get_instance();
	obj->set_value(123);
	obj->info();
	obj->get_instance()->info();

	Singleton* obj2 = obj;
	obj2->info();
}