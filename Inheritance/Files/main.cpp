#include<iostream>
#include<fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	//cout => fout (ConsoleOutput => FileOutput)	std::ostream	=>		std::ofstream;	OutputFileStream
	//cin => fin   (ConsoleInput => FileInput)		std::istream	=>		std::ifstream;	InputFileStream
	//std::ostream/std::istream		- iostream;
	//std::ofstream/std::ifstream	- fstream;
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	//1)Создание потока:
	std::ofstream fout;
	//2)Открытие потока:
	//fout.open("File.txt");	//Поток открытый таким образом всегда будет перезаписывать файл.
	fout.open("File.txt", std::ios_base::app);	//Append - добавить в конец
	//3)Запись в поток:
	fout << "Hello Files" << endl;
	//4)Потоки обязательно нужно закрывать:
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//1) Создаем и открываем поток:
	std::ifstream fin("File.txt");

	//2) Проверяем, открылся ли поток:
	if (fin.is_open())
	{
		//3) Чтение из файла:
		while (!fin.eof())	//EndOfFile
		{
			std::string buffer;
			//fin >> buffer;
			std::getline(fin, buffer);
			cout << buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	//?) Закрываем поток:
	fin.close();

}