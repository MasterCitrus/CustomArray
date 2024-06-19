#pragma once
#include "Iterator.h"

#include <iostream>
#include <cmath>
#include <initializer_list>

template<typename T>
class Array
{
public:
	using iterator = Iterator<T>;
	using const_iterator = Iterator<T>;
	//CONSTRUCTORS & DESTRUCTOR
	Array();
	Array(const size_t count, const T& value = T());
	Array(const Array<T>& array);
	Array(std::initializer_list<T> init);
	~Array();

	//OPERATORS
	//Assignment operator
	Array<T>& operator=(const Array<T>& other);

	//Subscript operator
	T& operator[](const size_t index);

	T& operator[](const size_t index) const;

	//MEMBER FUNCTIONS
	//Add/Remove from end of array
	void PopBack();
	void PushBack(const T& value);

	//Add one or more elements to middle of array
	iterator Insert(const_iterator pos, const T& value);

	//Remove from middle of array, ordered and unordered
	iterator RemoveOrdered(const_iterator pos);
	iterator RemoveUnordered(const_iterator pos);

	//Allocate more or less space in array
	void Allocate(size_t chunk);
	void Deallocate(size_t chunk);

	//Clear array
	void Clear();

	//Search function
	iterator Find(const T& value);

	//Array information functions
	unsigned int Size() const;
	unsigned int Capacity() const;
	bool Empty();

	//Get elements
	T& Front();
	T& Back();

	//Iterators
	iterator begin() { return &data[0]; }
	iterator end() { return &data[size]; }
	const_iterator begin() const { return &data[0]; }
	const_iterator end() const { return &data[size]; }
	const_iterator cbegin() const noexcept { return &data[0]; }
	const_iterator cend() const noexcept { return &data[size]; }

private:
	unsigned int size;
	unsigned int capacity;
	T* data;
};

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
Array<T>::Array()
{
	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
Array<T>::Array(size_t count, const T& value)
{
	data = new T[count]{ value };
	size = count;
	capacity = count;
}

template<typename T>
Array<T>::Array(const Array<T>& array)
{
	data = new T[array.capacity];
	size = array.size;
	capacity = array.capacity;
	for (size_t i = 0; i < capacity; i++) data[i] = array.data[i];
}

template<typename T>
Array<T>::Array(std::initializer_list<T> init)
{
	data = new T[init.size()];
	size = init.size();
	capacity = init.size();
	int i = 0;
	for (auto& value : init)
	{
		data[i] = value;
		i++;
	}
}

template<typename T>
Array<T>::~Array()
{
	delete[] data;
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	data = new T[other.capacity];
	size = other.size;
	capacity = other.capacity;
	for (size_t i = 0; i < other.size; i++) data[i] = other.data[i];
	return *this;
}

template<typename T>
T& Array<T>::operator[](const size_t index)
{
	return data[index];
}

template<typename T>
T& Array<T>::operator[](const size_t index) const
{
	return data[index];
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
void Array<T>::PopBack()
{
	size--;
}

template<typename T>
void Array<T>::PushBack(const T& value)
{
	if (size == capacity) Allocate(std::ceil(capacity * 1.5));
	*end() = value;
	size++;
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
typename Array<T>::iterator Array<T>::Insert(const_iterator pos, const T& value)
{
	auto offset = pos - begin();
	if (size == capacity) Allocate(std::ceil(capacity * 1.5));
	pos = begin() + offset;
	PushBack(Back());
	for (auto it = end() - 1; it != pos; --it)
	{
		*it = *(it - 1);
	}
	*pos = value;
	return pos;
}

template<typename T>
typename Array<T>::iterator Array<T>::RemoveOrdered(const_iterator pos)
{
	for (auto it = pos; it != end() - 1; ++it)
	{
		*it = *(it + 1);
	}
	size--;
	return pos;
}

template<typename T>
typename Array<T>::iterator Array<T>::RemoveUnordered(const_iterator pos)
{
	*pos = *(end() - 1);
	size--;
	return pos;
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
void Array<T>::Allocate(size_t chunk)
{
	if (chunk == 0) return;
	Array temp;
	temp = *this;
	data = new T[capacity + chunk];
	capacity += chunk;
	for (size_t i = 0; i < temp.Size(); i++) data[i] = temp.data[i];
}

template<typename T>
void Array<T>::Deallocate(size_t chunk)
{
	if (chunk >= capacity || chunk == 0) return;
	Array temp;
	temp = *this;
	size_t newCap;
	newCap = capacity - chunk;
	data = new T[newCap];
	capacity = newCap;
	if (newCap < size)
	{
		int diff = size - newCap;
		for (size_t i = 0; i < size - diff; i++) data[i] = temp.data[i];
	}
	else
	{
		for (size_t i = 0; i < size; i++) data[i] = temp.data[i];
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
void Array<T>::Clear()
{
	delete[] data;
	data = new T[capacity];
	size = 0;
}

template<typename T>
typename Array<T>::iterator Array<T>::Find(const T& value)
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (*it == value) return it;
	}
	return end();
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
unsigned int Array<T>::Size() const
{
	return size;
}

template<typename T>
unsigned int Array<T>::Capacity() const
{
	return capacity;
}

template<typename T>
inline bool Array<T>::Empty()
{
	return begin() = end();
}

//------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
T& Array<T>::Front()
{
	return *begin();
}

template<typename T>
T& Array<T>::Back()
{
	return *(end() - 1);
}
