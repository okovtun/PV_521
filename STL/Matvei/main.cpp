#define _CRT_SECURE_NO_WARNINGS
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
	{1, "ѕарковка в неположенном месте"},
	{2, "Ќепристегнутый ремень безопасности"},
	{3, "ѕересечение сплошной"},
	{4, "ѕревышение скорости"},
	{5, "ѕроезд на красный"},
	{6, "¬ыезд на встречную полосу"},
	{7, "≈зда в нетрезвом состо€нии"},
	{8, "ќскорбление офицера"},
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
			//функци€ atoi() - ASCII ti INT, преобразует входную строку в целое число
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

//#define INIT_BASE
//#define INIT_BASE_2
#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef INIT_BASE
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777aa", {Crime(4, "ул.Ћенина"), Crime(5,"ул.Ћенина"), Crime(7,"ул. Ёнтузиастов"), Crime(8,"ул.Ёнтузиастов")}},
		{"a123бб", {Crime(2, "ул.ѕролетарска€"), Crime(3,"ул.¬атутина")}},
		{"a001ев", {Crime(5, "ул.ќктр€брьска€"), Crime(5,"ул.ќкт€брьска€"), Crime(7,"ул. Ёнтузиастов"), Crime(8,"ул.Ёнтузиастов")}},
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef INIT_BASE_2
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777aa", {Crime(4, " ул.Ћенина", "2024.04.04 16:04"), Crime(5," ул.Ћенина", "2024.04.04 16:14"), Crime(7," ул. Ёнтузиастов", "2024.04.04 16:24"), Crime(8," ул.Ёнтузиастов", "2024.04.04 16:34")}},
		{"a123бб", {Crime(2, " ул.ѕролетарска€", "2025.01.05 11:12"), Crime(3," ул.¬атутина", "2025.01.06 15:25")}},
		{"a001ев", {Crime(5, " ул.ќктр€брьска€", "2024.07.08 19:08"), Crime(5," ул.ќкт€брьска€", "2024.07.08 19:28"), Crime(7," ул. Ёнтузиастов", "2024.07.08 19:38"), Crime(8," ул.Ёнтузиастов", "2024.07.08 19:48")}},
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);

#endif // LOAD_CHECK

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
			cout << license_plate << "\t";
			const int SIZE = 1024 * 500;
			char all_crimes[SIZE];
			fin.getline(all_crimes, SIZE);
			cout << all_crimes << endl;
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
				Stringstream - это объект, который хранит строку, но позвол€ет работать с ней, как с потоком. ј именно из строки можно читать различные еЄ элементы, использу€ операторы перенаправлени€ в поток и потоковую функцию get_line.
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