#include"List.h"
#include"List.cpp"

//#define BASE_CHECK
//#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	list.pop_front();
	list.print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef HOME_WORK
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	//list1.print();
	//list2.print();
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;;;;;;;;;;;;;;;;;;;;;;;;;;;
	for (List<int>::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
	}
	for (List<int>::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		//*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
#endif // HOME_WORK

	List<double> d_list = { 2.7, 3.14, 5.8, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни" , "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;

}