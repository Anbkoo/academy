#include <iostream>
#include <set>
#include <string>
#include "allocator.h"

int main()
	{
	CustomAllocator memory_pool(100);
	int* a = static_cast<int*>(memory_pool.allocate(10));
	memory_pool.printList();
	int* f = static_cast<int*>(memory_pool.allocate(200));
	int* d = static_cast<int*>(memory_pool.allocate(20));
	int* e = static_cast<int*>(memory_pool.allocate(30));
	memory_pool.printList();
	memory_pool.deallocate(d);
	memory_pool.printList();

	int* b = static_cast<int*>(memory_pool.allocate(12));
	memory_pool.printList();
	int* c = static_cast<int*>(memory_pool.allocate(7));
	int* g = static_cast<int*>(memory_pool.allocate(5));
	int* k = static_cast<int*>(memory_pool.allocate(1));
	memory_pool.printList();

	memory_pool.deallocate(b);
	memory_pool.printList();

	std::cin.get();
	return 0;
	}