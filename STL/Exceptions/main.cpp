#include<iostream>
#include<cmath>
using namespace std;

long long int Factorial(int n);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите число: "; cin >> n;
	try
	{
		cout << n << "! = " << Factorial(n) << endl;
	}
	/*catch (const char* e)
	{
		std::cerr << e << endl;
	}*/
	catch (const std::runtime_error& e)
	{
		std::cerr << "runtime_error:";
		std::cerr << e.what() << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception:";
		std::cerr << e.what() << endl;
	}
}

long long int Factorial(int n)
{
	if (n > 20)throw std::runtime_error("Arithmetical overflow exception");
	long long int f = 1;
	for (int i = 1; i <= n; i++)
	{
		f *= i;
	}
	return f;
}