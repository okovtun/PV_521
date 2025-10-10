#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<fstream>
#include <map>
#include <string>
#include <sstream>
#include <list>
#include <time.h>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0, "N/A"},
	{1, "Парковка в неположенном месте"},
	{2, "Непристегнутый ремень безопасности"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Проезд на красный"},
	{6, "Выезд на встречную полосу"},
	{7, "Езда в нетрезвом состоянии"},
	{8, "Оскорбление офицера"},
};
class Crime;
std::stringstream& operator >> (std::stringstream& stream, Crime& obj);
class Crime
{
	int violation;
	std::string place;
	tm time;
public:
	int get_violation()const
	{
		return violation;
	}
	const std::string& get_place()const
	{
		return place;
	}
	std::string get_time()const
	{
		char stringtime[256]{};
		strcpy(stringtime, asctime(&time));
		stringtime[strlen(stringtime) - 1] = 0;
		return stringtime;
	}
	time_t get_timestamp()const
	{
		tm time_copy = time;
		return mktime(&time_copy);
	}
	void set_violation(int violation)
	{
		this->violation = violation;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		char timestring[256] = {};
		strcpy(timestring, time.c_str());
		//YYYY.MM.DD HH:MM
		int parts[5] = {};
		int n = 0;
		const char delimiters[] = "./-: ";
		for (char* pch = strtok(timestring, delimiters); pch; pch = strtok(NULL, delimiters))
			//функция atoi() - ASCII ti INT, преобразует входную строку в целое число
			parts[n++] = std::atoi(pch);
		this->time = {};
		this->time.tm_year = parts[0] - 1900;
		this->time.tm_mon = parts[1] - 1;
		this->time.tm_mday = parts[2];
		this->time.tm_hour = parts[3];
		this->time.tm_min = parts[4];
	}
	void set_time(time_t time)
	{
		this->time = *localtime(&time);
	}
	Crime(int violation, const std::string& place, const std::string& time)
	{
		set_violation(violation);
		set_place(place);
		set_time(time);
	}
	Crime(int violation, const std::string& place, time_t time)
	{
		set_violation(violation);
		set_place(place);
		set_time(time);
	}

	explicit Crime(std::string str)
	{
		std::stringstream stream(str);
		stream >> *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	os.width(44);
	os << std::left;
	return os << obj.get_time() << VIOLATIONS.at(obj.get_violation()) << obj.get_place() << " " << obj.get_timestamp();
}

std::ofstream& operator << (std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_violation() << " " << obj.get_timestamp() << " " << obj.get_place();
	return ofs;
}

std::stringstream& operator >> (std::stringstream& stream, Crime& obj)
{
	int violation;
	stream >> violation;
	time_t time;
	stream >> time;
	obj.set_time(time);
	std::string place;
	std::getline(stream, place);
	obj.set_violation(violation);
	obj.set_place(place);
	return stream;
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
std::map<std::string, std::list<Crime>> load(const std::string& filename);

void add_crime(std::map<std::string, std::list<Crime>>& base);
void print_range(std::map<std::string, std::list<Crime>>& base);
void menu(std::map<std::string, std::list<Crime>>& base);

//#define INIT_BASE
//#define INIT_BASE_2
//#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef INIT_BASE
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777aa", {Crime(4, "ул.Ленина"), Crime(5,"ул.Ленина"), Crime(7,"ул. Энтузиастов"), Crime(8,"ул.Энтузиастов")}},
		{"a123бб", {Crime(2, "ул.Пролетарская"), Crime(3,"ул.Ватутина")}},
		{"a001ев", {Crime(5, "ул.Октрябрьская"), Crime(5,"ул.Октябрьская"), Crime(7,"ул. Энтузиастов"), Crime(8,"ул.Энтузиастов")}},
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef INIT_BASE_2
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777aa", {Crime(4, " ул.Ленина", "2024.04.04 16:04"), Crime(5," ул.Ленина", "2024.04.04 16:14"), Crime(7," ул. Энтузиастов", "2024.04.04 16:24"), Crime(8," ул.Энтузиастов", "2024.04.04 16:34")}},
		{"a123бб", {Crime(2, " ул.Пролетарская", "2025.01.05 11:12"), Crime(3," ул.Ватутина", "2025.01.06 15:25")}},
		{"a001ев", {Crime(5, " ул.Октрябрьская", "2024.07.08 19:08"), Crime(5," ул.Октябрьская", "2024.07.08 19:28"), Crime(7," ул. Энтузиастов", "2024.07.08 19:38"), Crime(8," ул.Энтузиастов", "2024.07.08 19:48")}},
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);
#endif // LOAD_CHECK

	std::map<std::string, std::list<Crime>> base = load("base.txt");
	menu(base);

}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator plate = base.begin(); plate != base.end(); ++plate)
	{
		fout << plate->first << ":";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			fout << *violation << ",";
		}
		fout << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator plate = base.begin(); plate != base.end(); ++plate)
	{
		cout << plate->first << ":\n";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			cout << "\t" << *violation << endl;
		}
		cout << delimiter;
	}
}

std::map<std::string, std::list<Crime>> load(const std::string& filename)
{
	std::map<std::string, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string license_plate;
			std::getline(fin, license_plate, ':');
			//cout << license_plate << "\t";
			const int SIZE = 1024 * 500;
			char all_crimes[SIZE];
			fin.getline(all_crimes, SIZE);
			//cout << all_crimes << endl;
			const char delimiters[] = ",";
			for (char* pch = strtok(all_crimes, delimiters); pch; pch = strtok(NULL, delimiters))
				base[license_plate].push_back(Crime(pch));
			{
				/*
				Crime crime(0, "");
				std::stringstream stream(pch);
				stream >> crime;
				base[license_plate].push_back(crime);
				*/
				/*
				Stringstream - это объект, который хранит строку, но позволяет работать с ней, как с потоком. А именно из строки можно читать различные её элементы, используя операторы перенаправления в поток и потоковую функцию get_line.
				*/
			}
		}
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	fin.close();
	return base;
}
void add_crime(std::map<std::string, std::list<Crime>>& base)
{
	std::string licence_plate;
	std::string place;
	cout << "Введите номер автомобиля: ";
	SetConsoleCP(1251);
	cin >> licence_plate;
	SetConsoleCP(866);

	cout << "Введите место происшествия: ";
	cin.ignore();
	cin.clear();
	SetConsoleCP(1251);
	std::getline(cin, place);
	SetConsoleCP(866);

	for (std::pair<int, std::string> violation : VIOLATIONS)
	{
		cout << violation.first << "\t" << violation.second << endl;
	}
	int number;
	cout << "Введите номер статьи: "; cin >> number;
	base[licence_plate].push_back(Crime(number, place, time(NULL)));
}
void print_range(std::map<std::string, std::list<Crime>>& base)
{
	std::string first, last;
	cout << "Введите начальный номер: "; 
	SetConsoleCP(1251);
	cin >> first;
	SetConsoleCP(866);
	cout << "Введите конечный номер: ";
	SetConsoleCP(1251);
	cin >> last;
	SetConsoleCP(866);
	for (
		std::map<std::string, std::list<Crime>>::iterator plate = base.lower_bound(first);
		plate != base.upper_bound(last);
		++plate
		)
	{
		cout << plate->first << ":\n";
		for (std::list<Crime>::iterator crime = plate->second.begin(); crime != plate->second.end(); ++crime)
		{
			cout << "\t" << *crime << endl;
		}
		cout << delimiter << endl;
	}
}
void menu(std::map<std::string, std::list<Crime>>& base)
{
	int var;
	do
	{
		cout << "1. Полный вывод Базы;" << endl;
		cout << "2. Сохранить;" << endl;
		cout << "3. Загрузить;" << endl;
		cout << "4. Добавить нарушение;" << endl;
		cout << "5. Вывод диапазона номеров;" << endl;
		cout << "0. Выдох;" << endl;

		cin >> var;
		system("CLS");
		switch (var)
		{
		case 1: print(base); break;
		case 2: save(base, "base.txt"); break;
		case 3: base = load("base.txt"); break;
		case 4: add_crime(base); break;
		case 5: print_range(base); break;
		default: std::cerr << "Error: Нажимйте пожалуйста на кнопки внимательнее!" << endl;
		}
	} while (var);
}