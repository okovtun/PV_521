#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------------\n"

class String
{
	int size;	//размер строки в Байтах (с учетом NULL-Terminator)
	char* str;	//адрес строки в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	//			Constructors:
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		//Конструктор по умолчанию создает пустую строку размером 80 Байт
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char* str) :String(strlen(str) + 1)
	{
		//this->size = strlen(str) + 1;	//strlen() возвращает размер строки в символах, +1 нужен чтобы выделилась память под NULL-Terminator
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	//CopyConstructor,CopyAssignment DeepCopy
	//CopyMethods, CopySemantic
	//Shallow copy - поверхностное копирование
	String(const String& other) :String(other.str)
	{
		//this->str = other.str;	//Shallow copy
		/// ------------------------------------------------ ///
		//Deep copy:
		//this->size = other.size;
		//this->str = new char[size] {};
		//for (int i = 0; i < size; i++)	this->str[i] = other.str[i];

		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other) :size(other.size), str(other.str)
	{
		//MoveConstructor - ShallowCopy:
		//this->size = other.size;
		//this->str = other.str;
		//Обнуляем принимаемый объект для того чтобы предотвратить удалене его ресурсов деструктором.
		other.size = 0;
		other.str = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] str;
		str = nullptr;
		size = 0;
		cout << "Destructor:\t\t" << this << endl;
		/*
		-----------------------------------
		Ошибка на этапе выполнения 'Debug Assertion Failed'
		возникает когда оператор delete[] выполняется 2 раза
		по одному адресу либо, оператору delete[] был передан
		адрес статической памяти.
		-----------------------------------
		*/
	}

	//				Operators:
	String& operator=(const String& other)
	{
		//this->str = other.str;	//Shallow copy - Повехностное копирование
		/// ------------------------------------- ///
		//0) Проверяем, не является ли тот объект этим объектом:
		if (this == &other)return *this;
		//1) Удаляем старую динамическую память
		delete[] this->str;
		//Deep copy - Побитовое копирование:
		this->size = other.size;
		//2) Выделяем новую динамическую память:
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		//0) Проверка, не являются ли 'this' и 'other' одним и тем же объектом.
		if (this == &other)return *this;
		//1) Кдаление старой памяти
		delete[] str;
		//2) Shallow copy:
		this->size = other.size;
		this->str = other.str;
		//3) Обнуляем принимаемый объект:
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}
	char operator[](int i)const
	{
		return str[i];	//Index operator, Subscript operator
	}
	char& operator[](int i)
	{
		return str[i];
	}


	//				Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};
String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		result[i] = left[i];
	//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
	//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

void Clear(char* str)
{
	delete[] str;
}

//#define CONSTRUCTORS_CHECK
//#define COPY_SEMANTIC_CHECK

void main()
{
	setlocale(LC_ALL, "");

	int a = 2;
	a = 3;

#ifdef CONSTRUCTORS_CHECK
	String str1;
	str1.print();

	String str2(5);	//Conversion from 'int' to 'String'
	str2.print();

	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;

	String str4 = "World";
	cout << str4 << endl;

	cout << delimiter << endl;
	String str5;
	str5 = str3 + str4;
	cout << delimiter << endl;
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK
	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2;
	str2 = str1;
	cout << str2 << endl;



	/*char* str = new char[8]{ "Hello" };
	cout << str << endl;
	Clear(str);
	Clear(str);*/
	//delete[] str;
	/*int arr[] = { 3,5,8,13,21 };
	delete[] arr;*/
#endif // COPY_SEMANTIC_CHECK

	//MoveMethods (MoveSemantic)

	String str1;	//DefaultConstructor
	str1.print();

	String str2(5);//Single-argument Constructor (int)
	str2.print();

	String str3 = "Hello";	//Single-argument Constructor (const char str[])
	str3.print();

	String str4();	//В этой строке НЕ вызывается DefaultConstructor, и НЕ создается объект,
					//здесь объявляется функция 'str4', которая ничего не принимает,
					//и возвращает значение типа 'String'.
	//str4 НЕ является объектом.

	//То есть, круглые скобки не делают явный вывоз конструктора по умолчанию,
	//если есть необходимость явно вызвать конструктор по умолчанию,
	//то это можно сделать при помощи фигурных скобок:

	String str5{};	//А эта строка уже явно вызывает DefaultConstructor()
	str5.print();

	String str6{ 6 };	//Single-argument Constructor (int)
	str6.print();

	String str7{ "World" };
	str7.print();

	String str8 = str7;	//CopyConstructor
	str8.print();

	String str9(str8);
	str9.print();

	String str10{ str9 };
	str10.print();

	//!!! Фигурные скобки для вызова конструкторов следует использовать с большой осторожностью	!!!

	String str11 = str3 + str8;
	str11.print();

}