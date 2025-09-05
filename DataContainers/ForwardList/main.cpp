//ForwardList
#include<iostream>
#include<time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

class Element
{
	int Data;			//Значение элемента
	Element* pNext;		//Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class ForwardList
{
	Element* Head;
	size_t size;	
public:
	Element* get_Head()const
	{
		return Head;
	}
	size_t get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//Конструктор по умолчанию - создает пустой список.
		Head = nullptr;		//Если список пуст, то его Голова указывает на 0.
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		//Deep copy (Побитовое копирование):
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head)pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end-t_start)/CLOCKS_PER_SEC << endl;
	}

	//			Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;	//0) Проверяем, не являются ли 'this' и 'other' одним объектом.
		while (Head)pop_front();			//1) Старое значение объекта удаляется из памяти
		//2) Deep copy (Побитовое копирование):
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		////1) Создаем элемент и сохраняем в него добавляемое значение:
		//Element* New = new Element(Data);

		////2) Привязываем новый, созданный элемент к началу списка:
		//New->pNext = Head;

		////3) Переносим Голову на новый элемент (Отправляем новый элемент в Голову):
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		//1) Доходим до нужного элемента (элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		////2) Создаем доьавляемый элемент:
		//Element* New = new Element(Data);
		////3) Пристыковываем новый элемент к его следующему элемену:
		//New->pNext = Temp->pNext;
		////4) Пристыковываем предыдущий элемент к новому:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//					Methods:
	void print()const
	{
		/*
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно перебирать элементы стуктуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		Temp;	//Указатель 'Temp';
		//Temp->;	//Элемент 'Temp';
		*/

		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов:  " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);

	return fusion;
}

//#define BASE_CHECK
#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element = 5;

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int a = 2;
	int b = 3;
	int c = a + b;

	//ForwardList fusion = list1 + list2;		//CopyConstructor
	ForwardList fusion;
	cout << delimiter << endl;
	fusion = list1 + list2;		//CopyAssignment
	cout << delimiter << endl;
	fusion.print();

	/*
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();
	*/

#endif

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "ForwardList filled for " << double(t_end - t_start)/CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK


}