#pragma once
#include <iostream>
using namespace std;
template<typename T>
struct snode
{
	snode() {
		data = 0;
		next = nullptr;
	}
	T data;		// Данные
	snode<T>* next;	// Адрес следующего элемента списка
};

template<typename T>
class SList {
	snode<T>* first;								// Адрес первого элемента списка
	snode<T>* last;								// Адрес последнего элемента списка
	size_t count;								// Количество элементов в списке
	size_t iterator;							// Итератор
public:
	SList();									// конструктор по умолчанию
	SList(const SList<T>& data);					// конструктор копирования
	SList(SList<T>&& data);						// конструктор перемещения
	SList<T>& operator=(const SList<T>& data);	// оператор равно копированием
	SList<T>& operator=(SList<T>&& data);		// оператор равно перемещением
	T& operator[](size_t pos);					// оператор индексирования

	void AddToHead(const T& data);				// добавление элемента в начало 
	void AddToTail(const T& data);				// добавление элемента в конец 
	T front();									// возвращает первое значение
	T back();									// возвращает последнее значение
	T DeleteFromHead();							// удаление первого элемента
	T DeleteFromTail();							// удаление последнего элемента
	void DeleteAll();							// удаление всех элементов
	void Show();								// отображение всех элементов
	size_t size();								// количество элементов

	void InsertAt(size_t pos, const T& data);	// вставка в указанную позицию
	void DeleteAt(size_t pos);					// удаление по указанной позиции
	size_t Find(const T& data);					// поиск элемента (0 в случае неудачи)
	size_t FindAndReplace(const T& data, const T& repldata);	// поиск и замена всех элементов
	void reverse();								// переворот списка

	void sort();								// сортирует элементы
	void splice(const SList<T>& data);			// перемещает элементы из другого list 

	~SList();									// деструктор
};

template<typename T>
inline SList<T>::SList()
{
	first = nullptr;
	last = nullptr;
	count = 0;
	iterator = 0;
}

template<typename T>
inline SList<T>::SList(const SList<T>& data) : SList()
{
	snode<T>* temp = data.first;
	while (temp->next) {
		snode<T>* vova = new snode<T>;
		vova->data = temp->data;
		if (this->last == nullptr) this->first = this->last = vova;
		else this->last->next = vova;
		this->last = vova;
		temp = temp->next;
	}
}

template<typename T>
inline SList<T>::SList(SList<T>&& data)
{
	this->first = data->first;
	this->last = data->last;
	data->first = data->last = nullptr;
}

template<typename T>
inline SList<T>& SList<T>::operator=(const SList<T>& data)
{
	snode<T>* temp = data.first;
	while (temp->next) {
		snode<T>* vova = new snode<T>;
		vova->data = temp->data;
		if (this->last == nullptr) this->first = this->last = vova;
		else this->last->next = vova;
		this->last = vova;
		temp = temp->next;
	}
	return*this;
	// TODO: вставьте здесь оператор return
}

template<typename T>
inline SList<T>& SList<T>::operator=(SList<T>&& data)
{
	this->first = data->first;
	this->last = data->last;
	data->first = data->last = nullptr;
	return*this;
	// TODO: вставьте здесь оператор return
}

template<typename T>
inline T& SList<T>::operator[](size_t pos)
{
	snode<T>* temp = this->first;
	float  index = 0;
	while (temp->next) {
		if (index == pos) return temp->data;
		temp = temp->next;
		index++;
	}
	// TODO: вставьте здесь оператор return
	return index;
}

template<typename T>
inline void SList<T>::AddToHead(const T& data)
{
	snode<T>* temp = new snode<T>;
	temp->data = data;
	temp->next = first;
	this->first = temp;
}

template<typename T>
inline void SList<T>::AddToTail(const T& data)
{
	snode<T>* temp = new snode<T>;
	temp->data = data;
	this->last->next = temp;
	this->last = temp;
}

template<typename T>
inline T SList<T>::front()
{
	return this->first->data();
}

template<typename T>
inline T SList<T>::back()
{
	snode<T>* temp = this->first;
	T vova;
	while (temp->next != this->last)
	{
		temp->data = temp->next->data;
	}
	vova = temp->data;
	return vova;
}

template<typename T>
inline T SList<T>::DeleteFromHead()
{
	snode<T>* temp = this->first;
	this->first = this->first->next;
	T vova = temp->data;
	delete temp;
	return vova;
}

template<typename T>
inline T SList<T>::DeleteFromTail()
{
	snode<T>* vova = this->last;
	snode<T>* temp = this->first;
	while (temp->next != this->last)
	{
		temp = temp->next;
	}
	T name = vova->data;
	delete vova;
	return name;
}

template<typename T>
inline void SList<T>::DeleteAll()
{
	snode<T>* temp = this->first;
	while (temp->next != NULL)
	{
		temp = temp->next;
		delete temp;
	}
}

template<typename T>
inline void SList<T>::Show()
{
	snode<T>* temp = this->first;
	while (temp->next != NULL)
	{
		temp = temp->next;
		cout << temp->data << " ";
	}
}

template<typename T>
inline size_t SList<T>::size()
{
	T count = 0;
	snode<T>* temp = this->first;
	while (temp->next != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

template<typename T>
inline void SList<T>::InsertAt(size_t pos, const T& data)
{
	snode<T>* temp = new snode<T>;
	size_t number = 0;
	if (temp == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}
	else
	{
		snode<T>* beg = temp;
		do {
			++number;
			temp = temp->next;
		} while (temp != nullptr);
		if (pos > number) {
			cout << "Invalid position" << endl;
			return;
		}
		temp = beg;
		for (size_t i = 0; i < number; i++)
		{
			if (pos == i)
			{
				snode<T>* n_temp = new snode<T>;
				n_temp->data = data;
				n_temp->next = temp->next;
				temp->next = n_temp;
			}
			else
				temp = temp->next;
		}
	}
}

template<typename T>
inline void SList<T>::DeleteAt(size_t pos)
{
	if (first != nullptr && pos < SList<T>::size() && pos >= 0) {
		snode<T>* temp = first;
		snode<T>* helping = first;

		for (size_t i = 0; i < pos; i++)
		{
			helping = temp;
			temp = temp->next;
		}

		if (temp == first)
		{
			first = temp->next;
		}
		else
		{
			helping->next = temp->next;
		}
		cout << "Удаляемый элемент: " << temp;
		free(temp);
		T new_size = SList<T>::size() - 1;
	}
}

template<typename T>
inline size_t SList<T>::Find(const T& data)
{
	snode<T>* temp = first;
	while (temp != 0) {

		if (temp->data == data) {
			cout << "find";
		}
		temp = temp->next;
	}
	return temp->data;
}

template<typename T>
inline void SList<T>::reverse()
{
	if (first == NULL) return;
	struct snode<T>* curr, * next, * prev = NULL;
	curr = first;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	first = prev;
}

template<typename T>
inline void SList<T>::sort()
{
	snode<T>* new_first = nullptr;
	while (first != nullptr)
	{
		snode<T>* node = first;
		first = first->next;
		if (new_first == nullptr || node->data < new_first->data)
		{
			node->next = new_first;
			new_first = node;
		}
		else
		{
			snode<T>* current = new_first;
			while (current->next != nullptr && !(node->data < current->next->data))
			{
				current = current->next;
			}
			node->next = current->next;
			current->next = node;
		}
	}
}

template<typename T>
inline SList<T>::~SList()
{
	while (first)
	{
		snode<T>* temp = first->next;
		delete first;
		first = temp;
	}
}

