//AssociativeContainers
#include<iostream>
#include<string>
#include<map>
#include<list>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n----------------------------------\n"

#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_MAP
	//map - это контейнер, каждый элемент которого представляет собой пару "ключ:значение" pair<key,value>
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Воскресенье"),
		std::pair<int, std::string>(1, "Понедрельник"),
		std::pair<int, std::string>(2, "Вторник"),
		std::pair<int, std::string>(3, "Среда"),
		{4, "Четверг"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{6, "Суббота"},
		{7, "Воскресенье"},
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << delimiter << endl;
	for (std::pair<int, std::string> i : week)
	{
		cout << i.first << tab << i.second << endl;
	}
	cout << delimiter << endl;

	std::map<std::string, std::list<std::string>> dictionary =
	{
		{"occasionaly",{"иногда", "время от времени", "случайно", "изредка"}},
		{"causes",{"причина", "приводить к..."}},
		{"space",{"космос", "пространство", "пробел"}},
		{"void",{"пустота", "вакуум"}},
		{"sequence",{"последовательность", "ряр", "эпизод", "череда"}},
		{"consequence",{"следствие", "последствие", "вывод"}},
	};

#endif // STL_MAP

}

/*
map;
set;
multimap;
multiset;
*/