#include "PrimeNumber.Core/PrimeNumberCalculator.h"
#include <math.h>
#include <iostream>

PrimeNumberCalculator::PrimeNumberCalculator() = default;

std::vector<size_t> PrimeNumberCalculator::GetPrimeNumbers(size_t i_till_value)
	{
	std::vector<size_t> temp;
	temp.reserve(i_till_value / 3.14);
	for (size_t i = 1; i <= i_till_value; i++)
		{
		if (check_is_prime(i))
			{
			temp.emplace_back(i);
			}
		}
	return temp;
	}
