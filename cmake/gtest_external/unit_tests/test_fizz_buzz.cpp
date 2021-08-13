#include "fizzBuzz.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Fizz_Buzz_Get, ReturnFizz_When_Set6)
	{
	fizzBuzz _number;
	const auto result = _number.check_number_is_fizzBuzz(6);
	std::cout << "hello";
	EXPECT_EQ(result, "Fizz");
	}

TEST(Fizz_Buzz_Get, ReturnBuzz_When_Set5)
	{
	fizzBuzz _number;
	const auto result = _number.check_number_is_fizzBuzz(5);
	EXPECT_EQ(result, "Buzz");
	}

TEST(Fizz_Buzz_Get, ReturnBoth_When_Set30)
	{
	fizzBuzz _number;
	const auto result = _number.check_number_is_fizzBuzz(30);
	EXPECT_EQ(result, "Fizz Buzz");
	}