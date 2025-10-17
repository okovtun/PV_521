/*
------------------------------------
STL - Standard Template Library
1. Container - это объект, который организует хранение других объектов в памяти;
2. Iterators - это указатель, при помощи которого можно перемещаться по элементам контейнера;
3. Algorithm - это самые обычные функции, выполняюшие операции над контейнерами, такие как поиск, сортировка и т.д.;
4. Predicate - это функция, которая возвращает 'true' или 'false';
5. Allocator - это функция, которая выделяет память;
6. Functional object;
------------------------------------
			Containers:
1. Sequence containers:		array, vector, deque, forward_list, list;
2. Associative containeres:	map, set, multimap, multiset;
3. Conteiner adaptors:		stack, queue(очередь), priority_queue(очередь с приоритетами);
4. Unordered associative containers(нсортированные ассоциативные контейнеры):
							unordered_map. unordered_set, unordered_multimap, unordered_multiset;
------------------------------------
*/

#include<iostream>
#include<list>
#include<set>
using std::cin;
using std::cout;
using std::endl;

class Integer
{
	int number;
public:
	int get_number()const
	{
		return number;
	}
	void set_number(int number)
	{
		this->number = number;
	}
	Integer(int number = 0) :number(number) {}
	~Integer() {}
};
bool operator<(const Integer& left, const Integer& right)
{
	return left.get_number() < right.get_number();
}
std::ostream& operator<<(std::ostream& os, const Integer& obj)
{
	return os << obj.get_number();
}

void main()
{
	setlocale(LC_ALL, "");

	/*std::list<int> list = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;*/

	//Integer number = 3;
	//cout << number << endl;
	cout << (Integer(2) < Integer(5)) << endl;
	std::set<Integer> numbers = { 50, 25, 75, 16, 32, 58, 85 };
	for (Integer i : numbers)cout << i << "\t"; cout << endl;
}