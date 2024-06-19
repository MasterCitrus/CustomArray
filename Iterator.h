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

	Iterator& operator++()
	{
		++ptr;
		return*this;
	}
	Iterator operator++(int)
	{
		Iterator temp = *this;
		++ptr;
		return temp;
	}

	Iterator& operator--()
	{
		--ptr;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator temp = *this;
		--ptr;
		return temp;
	}

	Iterator& operator+=(difference_type n)
	{
		ptr += n;
		return *this;
	}
	Iterator& operator-=(difference_type n)
	{
		ptr -= n;
		return *this;
	}

	friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.ptr == rhs.ptr; }
	friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

	friend bool operator<(const Iterator& lhs, const Iterator& rhs) { return lhs.ptr < rhs.ptr; }
	friend bool operator>(const Iterator& lhs, const Iterator& rhs) { return rhs < lhs; }

	friend bool operator<=(const Iterator& lhs, const Iterator& rhs) { return !(rhs < lhs); }
	friend bool operator>=(const Iterator& lhs, const Iterator& rhs) { return !(lhs < rhs); }

	friend Iterator operator+(const Iterator& it, difference_type n)
	{
		Iterator temp = it;
		temp += n;
		return temp;
	}
	friend Iterator operator+(difference_type n, const Iterator& it)
	{
		return it + n;
	}

	friend Iterator operator-(const Iterator& it, difference_type n)
	{
		Iterator temp = it;
		temp -= n;
		return temp;
	}
	friend difference_type operator-(const Iterator& lhs, const Iterator& rhs)
	{
		return lhs.ptr - rhs.ptr;
	}

private:
	pointer ptr;
};