#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

/*
------------------------------
Class - обращение к обычному классу;
Class<type> - обращение к шаблонному классу. type определяет, какого типа будут поля создаваемого объекта.
template<typename T>
------------------------------
*/

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;	//Объекты классов и структур и указатели на эти объекты 
					//можно объявлять непосредственно после описания классов и структур.
	size_t size;	//Размер списка. size_t - это typedef на 'unsigned int'.
	class ConstBaseIterator
	{
		//Этот класс обощает свойства разных Итераторов
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		T operator*()const;
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//				Increment/Decrement:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	////////////////////////////////////////////////
	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//			Operators:
	List<T>& operator=(const List<T>& other);

	//			Adding Elements:
	void push_front(T Data);
	void push_back(T Data);

	void insert(T Data, int Index);

	//				Removing elements:
	void pop_front();
	void pop_back();

	//				Methods:
	void print()const;
	void reverse_print()const;
};

////////////////////////////////////////////////////////////////////////////////////
///////							Iterators									////////

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>T List<T>::ConstBaseIterator::operator*()const	//В константном итераторе должен быть только константный оператор разыменования,
						//здесь ни в коем случае НЕ должно быть обычного оператора разыменования
{
	return Temp->Data;
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}

//			type						name							parameters
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}


///////							Iterators									////////
////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////
///////						List member-functions							////////

template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
	cout << "ILConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//			Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}

//			Adding Elements:
template<typename T>void List<T>::push_front(T Data)
{
	//1) Создаем элемен, в котором будет храниться добавляемое значение:
	Element* New = new Element(Data);

	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		//2) Пристыковывем новый элемент к списку:
		New->pNext = Head;

		//3) Пристыковывем начальный элемент списка к новому элементу:
		Head->pPrev = New;

		//4) Делаем новый элемент начальным элементом списка:
		Head = New;
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	//1) Сздаем новый элемент:
	Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		//2) Цепляем новый элемент за Хвост списка:
		New->pPrev = Tail;

		//3) Пристыковывем список к новому элементу:
		Tail->pNext = New;

		//4) Делаем новый элемент Хвостом списка:
		Tail = New;
	}
	size++;
}

template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index < 0)return;
	if (Index == 0 || size == 0)return push_front(Data);
	if (Index >= size)return push_back(Data);
	//1) Доходим до нужного элемента:
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Независимо от того, каким образом мы дошли до нужного элемента, с начала списка или с конца списка,
	// процедура добавления элемента будет идентичной:
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	//2)Создаем новый элемент:
	Element* New = new Element(Data);

	//3)Пристыковываем новый элемент к списку:
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;

	//4)Вклиниваем новый элемент в список:
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;

	size++;
}

//				Removing elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)	//Если Голова и Хвост равны, значит они указывают либо на 0 либо на один и тот же элемент.
		//Ситуацию с пестым списком обрабатывает предыдущее условие.
		//Ситуацию с выроженным списком обрабатывает текущее условие, и в этом if-е удаляется один елинственный элемент списка.
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		//Общий случай:

		//1) Смещаем Голову на следующий элемент:
		Head = Head->pNext;

		//2) Удаляем элемент из памяти:
		delete Head->pPrev;

		//3) Обнуляем указатель на удаленный элемент (делаем Head последним элементом списка):
		Head->pPrev = nullptr;
	}

	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}

//				Methods:
template<typename T>void List<T>::print()const
{
	cout << delimiter << endl;
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail: " << Tail << endl;
	cout << "Количество элементов списка: " << size;
	cout << delimiter << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	cout << delimiter << endl;
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head: " << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}

///////						List member-functions							////////
////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////
///////							Global-functions							////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> fusion = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		fusion.push_back(*it);
	}
	return fusion;
}
///////							Global-functions							////////
////////////////////////////////////////////////////////////////////////////////////


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