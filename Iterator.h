#pragma once
#include <cstddef>
#include <iterator>

template<typename T>
class Iterator
{
public:
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::random_access_iterator_tag;

public:
	Iterator() : ptr{ nullptr } {}
	Iterator(pointer ptr) : ptr{ ptr } {}

	reference operator*() const { return *ptr; }
	pointer operator->() const { return ptr; }
	reference operator[](difference_type n) const { return *(ptr + n); }

	Iterator<T>& operator++()
	{
		++ptr;
		return *this;
	}
	Iterator<T> operator++(int)
	{
		Iterator<T> temp = *this;
		++ptr;
		return temp;
	}

	Iterator<T>& operator--()
	{
		--ptr;
		return *this;
	}
	Iterator<T> operator--(int)
	{
		Iterator<T> temp = *this;
		--ptr;
		return temp;
	}

	Iterator<T>& operator+=(difference_type n)
	{
		ptr += n;
		return *this;
	}
	Iterator<T>& operator-=(difference_type n)
	{
		ptr -= n;
		return *this;
	}

	friend bool operator==(const Iterator<T>& lhs, const Iterator<T>& rhs) { return lhs.ptr == rhs.ptr; }
	friend bool operator!=(const Iterator<T>& lhs, const Iterator<T>& rhs) { return !(lhs == rhs); }

	friend bool operator<(const Iterator<T>& lhs, const Iterator<T>& rhs) { return lhs.ptr < rhs.ptr; }
	friend bool operator>(const Iterator<T>& lhs, const Iterator<T>& rhs) { return rhs < lhs; }

	friend bool operator<=(const Iterator<T>& lhs, const Iterator<T>& rhs) { return !(rhs < lhs); }
	friend bool operator>=(const Iterator<T>& lhs, const Iterator<T>& rhs) { return !(lhs < rhs); }

	friend Iterator<T> operator+(const Iterator<T>& it, difference_type n)
	{
		Iterator<T> temp = it;
		temp += n;
		return temp;
	}
	friend Iterator<T> operator+(difference_type n, const Iterator<T>& it)
	{
		return it + n;
	}

	friend Iterator<T> operator-(const Iterator<T>& it, difference_type n)
	{
		Iterator<T> temp = it;
		temp -= n;
		return temp;
	}
	friend difference_type operator-(const Iterator<T>& lhs, const Iterator<T>& rhs)
	{
		return lhs.ptr - rhs.ptr;
	}

private:
	pointer ptr;
};