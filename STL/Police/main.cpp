#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n--------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0, "N/A"},
	{1, "�������� � ������������ �����"},
	{2, "������������� ������ ������������"},
	{3, "����������� �������"},
	{4, "���������� ��������"},
	{5, "������ �� �������"},
	{6, "����� �� ��������� ������"},
	{7, "���� � ��������� ���������"},
	{8, "����������� �������"},
};

class Crime
{
	int violation;
	std::string place;
public:
	int get_violation()const
	{
		return violation;
	}
	const std::string& get_place()const
	{
		return place;
	}
	void set_violation(int violation)
	{
		this->violation = violation;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	Crime(int violation, const std::string& place)
	{
		set_violation(violation);
		set_place(place);
	}
};
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	os.width(44);
	os << std::left;
	return os << VIOLATIONS.at(obj.get_violation()) << obj.get_place();
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777aa", {Crime(4, "��. ������"), Crime(5, "��. ������"), Crime(7, "��. �����������"), Crime(8, "��. �����������")} },
		{"a123bb", {Crime(2, "��. ������������"), Crime(3, "��. ��������")}	},
		{"a001eg", {Crime(5, "��. �����������"), Crime(5, "��. �����������"), Crime(7, "��. �����������"), Crime(8, "��. �����������")} }
	};
	print(base);
	save(base, "base.txt");
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
		cout << delimiter << endl;
	}
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator plate = base.begin(); plate != base.end(); ++plate)
	{
		fout << plate->first << ":\n";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			fout << "\t" << *violation << endl;
		}
		fout << delimiter << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
