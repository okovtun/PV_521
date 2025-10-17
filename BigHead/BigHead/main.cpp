#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	int N;
	cout << "Input number: "; cin >> N;
	for (int i = 1; i < N+1; i++)
	{
		for (int j = 1; j < N+1; j++)
		{
			if (j > i / 2 && j < (N + 1 - i / 2))
				cout << ".";
			else cout << "*";
		}
		cout << endl;
	}
}