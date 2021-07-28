#pragma once

#include <PrimeNumber.Core/PrimeNumber.Core.API.h>
#include <vector>

class PRIMENUMBERCORE_API PrimeNumberCalculator
  {
  public:
    PrimeNumberCalculator();

    std::vector<size_t> GetPrimeNumbers(size_t i_till_value);
  };

inline bool check_is_prime(size_t n)
	{
	if (n < 1)
		{
		return false;
		}
	else if (n == 2 || n == 1)
		return true;

	for (size_t i = 2; i < sqrt(n) + 1; i++)
		{
		if (n % i == 0)
			{
			return false;
			}
		}
	return true;
	}