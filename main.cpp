#include "Array.h"
#include <iostream>
#include <numeric>

template<typename T>
void PrintStats(Array<T> array)
{
	for (size_t i = 0; i < array.Size(); i++) std::cout << array[i] << std::endl;
	std::cout << "Size: " << array.Size() << "\nCapacity: " << array.Capacity() << std::endl << std::endl;
}

int main()
{
	Array<int> test(10, 1);
	Array<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	numbers.Insert(numbers.begin() + 5, 50);

	for (auto value : numbers) std::cout << value << "\n";
	std::cout << '\n';

	numbers.RemoveOrdered(numbers.begin() + 5);

	for (auto value : numbers) std::cout << value << "\n";

	numbers.RemoveUnordered(numbers.begin() + 5);

	for (auto value : numbers) std::cout << value << "\n";

	//auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
	//std::cout << sum << std::endl;

	//auto thing = numbers.Find(3);

	//if (thing != numbers.end()) std::cout << *thing << " has been found.\n";
	//else std::cout << "Not found.\n";

	//PrintStats(numbers);

	//numbers.PushBack(1);

	//PrintStats(numbers);

	//numbers.PopBack();

	//PrintStats(numbers);

	//numbers.Deallocate(20);

	//PrintStats(numbers);

	//numbers.Allocate(20);

	//PrintStats(numbers);

	//numbers.PushBack(3);

	//PrintStats(numbers);
}