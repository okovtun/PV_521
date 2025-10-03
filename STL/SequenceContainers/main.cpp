//SequenceContainers
#include<iostream>
#include<array>
#include<vector>
#include<deque>
#include<list>
#include<forward_list>
#include<iterator>
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimiter "\n-------------------------------------\n"

template<typename T>void vector_info(const std::vector<T>& vec);
template<typename T>void deque_info(const std::deque<T>& vec);

//#define STL_ARRAY
#define STL_VECTOR
#define STL_DEQUE
//#define STL_LIST
//#define STL_FORWARD_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива;
	throw;
	const int n = 5;
	std::array<int, n> arr;
	for (int i = 0; i < arr.size(); i++)
	{
		arr.at(i) = rand() % 100;
	}
	try
	{
		for (int i = 0; i < arr.size() * 2; i++)
		{
			cout << arr.at(i) << tab;
			//out_of_range exception
			//catch
			//throw
			//CPU - аппаратное исключение;
			//OS  - системное исключение;
			//Program - прикладное исключение;
		}
		/*cout << endl;
		int a, b;
		cout << "Input 2 numbers: "; cin >> a >> b;
		cout << a / b << endl;*/
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	/*catch (...)
	{
		std::cout << "Error: Something went wrong" << endl;
	}*/

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	std::string str;

#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.push_back(55);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
		cout << *it << tab;
	cout << endl;
	vector_info(vec);
	//vec.shrink_to_fit();	//урезает capacity до фактического размера
	vec.reserve(14);
	//vec.push_back(1024);
	//vec.resize(18);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	/////////////////////////////////////////
	int index;
	int value;
	do
	{
		cout << "Введите индекс добавляемого элемента: "; cin >> index;
		cout << "Введите значение добавляемого элемента: "; cin >> value;
	} while (index>vec.capacity());
	vec.insert(vec.begin() + index, value);
	for (int i : vec)cout << i << tab; cout << endl;

	do
	{
		cout << "Введите индекс добавляемого элемента: "; cin >> index;
	} while (index>vec.capacity());
	vec.erase(vec.begin() + index);
	for (int i : vec)cout << i << tab; cout << endl;

#endif // STL_VECTOR

#ifdef STL_DEQUE
	//deque - это контейнер, который хранит данные в виде списка Веторов.
	//Это позволяет обеспечить отоносительно быстрый доступ к элементам,
	//и относительно быстрое добавление/удаление элементов.
	//deque - Double-ended queue (двунаправленная очередь).
	//deque по своим возможностям очень напоминает vector,
	//и дополняет его методами push_front и pop_front.
	std::deque<int> deque = { 3, 5, 8, 13, 21 };
	deque.push_back(34);
	deque.push_front(2);

	/*std::vector<int>vec;
	cout << typeid(vec.data()).name() << endl;*/

	deque_info(deque);
	deque.assign(vec.begin()+3, vec.end()-3);
	for (int i : deque)cout << i << tab; cout << endl;

#endif // STL_DEQUE


#ifdef STL_LIST
	//list - это контейнер, который хранит данные в виде двусвязного списка.
	std::list<int> list = { 3, 5, 8, 13, 21, 34, 55, 89 };
	list.push_front(2);
	list.push_front(1);
	list.push_front(1);
	list.push_front(0);
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
		cout << *it << tab;
	cout << endl;

	for (std::list<int>::reverse_iterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;
	cout << endl;

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(list.begin() + index, value);	//Списки НЕ поодерживаю арифметику указателей
	std::list<int>::iterator position = list.begin();
	//for (int i = 0; i < index; i++)position++;
	//std::advance(position, index);	//Функция advance() смещает итератор вправо, на заданое количество элементов.
	//list.insert(position, value);

	std::list<int>::reverse_iterator r_positiion = list.rbegin();
	std::advance(r_positiion, list.size() - index);
	position = r_positiion.base();
	list.insert(position, value);

	for (int i : list)cout << i << tab; cout << endl;

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	position = list.begin();
	std::advance(position, index);
	list.erase(position);
	for (int i : list)cout << i << tab; cout << endl;

#endif // STL_LIST

#ifdef STL_FORWARD_LIST
	std::forward_list<int> list = { 3, 5, 8, 13, 21 };
	list.push_front(2);
	list.push_front(1);
	list.push_front(1);
	list.push_front(0);
	for (std::forward_list<int>::iterator it = list.begin(); it != list.end(); ++it)
		cout << *it << tab;
	cout << endl;

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::forward_list<int>::iterator position = list.before_begin();
	std::advance(position, index);
	list.insert_after(position, value);
	list.insert_after(list.begin(), 16384);
	for (int i : list)cout << i << tab; cout << endl;

#endif // STL_FORWARD_LIST

}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;		//Фактический размер Вектора, показывающий сколько элементов хранит Вектор.
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;	//Объем зарезервированной памяти. Зарезервированная память нужна для того,
	//чтобы ускорить процесс добавления элементов, и избежать необходимости переопределять память при каждом добавлении элемента,
	//это экономит ресурсы процессорного времени, но расходует дополнительные ресурсы памяти.
	//Если у Вектора есть свободная зарезервированная память, то добавляемое значение просто записывается в конец массива,
	//но если зарезервированная память законилась, то при добавлении элемента Вектор резервирует новую память,
	//в половину больше фактического размера.
	//На capacity можно повлиять при помощи методов reserve(), resize() и shrink_to_fit()
	cout << delimiter << endl;
}
template<typename T>void deque_info(const std::deque<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;		//Фактический размер Вектора, показывающий сколько элементов хранит Вектор.
	cout << "MaxSize: " << vec.max_size() << endl;
	//cout << "Capacity:" << vec.capacity() << endl;	
	cout << delimiter << endl;
}

/*
----------------------------------
try
{
	
}
catch(type1 name)
{
	....
}
catch(type2 name)
{
	....
}
.........
catch(type3 name)
{
	....
}
catch(...)
{
	....
}
----------------------------------
*/