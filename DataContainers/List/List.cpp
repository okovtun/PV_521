#include"List.h"

////////////////////////////////////////////////////////////////////////////////////
///////				Определение класса - Class definition					////////

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

///////			Конец определения класса - Class definition	end				////////
////////////////////////////////////////////////////////////////////////////////////

///-----------------------------------------------------------------------------///