#include "deque.h"
#include <vector>
#include <list>

int main()
	{
	list<int> custom(true);
	custom.insert_to_begin(5);
	custom.insert_to_begin(8);
	custom.insert_to_begin(9);
	custom.insert_to_end(20);

	list<int> custom2(false);
	custom2.insert_to_begin(1);
	custom2.insert_to_begin(2);
	custom2.insert_to_begin(3);
	custom2.insert_to_end(4);

	list<int> custom1(true);
	std::list<int> a = { 1, 2, 3 };

	return EXIT_SUCCESS;
	}