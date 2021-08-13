#pragma once
#include <iostream>
#include <string>

class fizzBuzz
	{
	public:
		std::string check_number_is_fizzBuzz(size_t _number)
			{
			if (_number % 3 == 0 && _number % 5 == 0)
				return "Fizz Buzz";
			else if (_number % 5 == 0)
				return "Buzz";
			else if (_number % 3 == 0)
				return "Fizz";
			}
	};