#include <PrimeNumber.Core/PrimeNumberCalculator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <string>
#include <functional>

class PrimeNumberCalculatorTest : public ::testing::Test
	{
	public:
		PrimeNumberCalculator* calc;
		PrimeNumberCalculatorTest()
			{
			calc = new PrimeNumberCalculator;
			}
		~PrimeNumberCalculatorTest()
			{
			delete calc;
			}
	};

TEST(PrimeNumberCalculator_GetPrimeNumbers, Has2_When_Till15)
	{
	//setup
	PrimeNumberCalculator calc;
	//act
	const auto result = calc.GetPrimeNumbers(15);
	//assert
	EXPECT_THAT(result, ::testing::Contains(2));
	}


TEST(PrimeNumberCalculator_GetPrimeNumbers, Has1_When_Till15)
	{
	PrimeNumberCalculator calc;
	const auto result = calc.GetPrimeNumbers(15);
	EXPECT_THAT(result, ::testing::Contains(1));
	}

TEST(PrimeNumberCalculator_GetPrimeNumbers, Has991_When_Till1000)
	{
	PrimeNumberCalculator calc;
	const auto result = calc.GetPrimeNumbers(1000);
	EXPECT_THAT(result, ::testing::Contains(991));
	}

TEST_F(PrimeNumberCalculatorTest, Has9967_When_Till1000)
	{
	const auto result = calc->GetPrimeNumbers(10'000);
	EXPECT_THAT(result, ::testing::Contains(9967));
	}

TEST_F(PrimeNumberCalculatorTest, NotHas0_When_Till15)
	{
	const auto result = calc->GetPrimeNumbers(15);
	EXPECT_THAT(result, ::testing::Not(::testing::Contains(0)));
	}


class PrimeNumberCalculatorParametrTest : public PrimeNumberCalculatorTest, public testing::WithParamInterface<std::tuple<size_t, size_t>>
	{
	public:
		std::vector<size_t> result;
		PrimeNumberCalculatorParametrTest()
			{
			result = calc->GetPrimeNumbers(std::get<0>(GetParam()));
			}
	};

INSTANTIATE_TEST_SUITE_P(PrimeNumber, PrimeNumberCalculatorParametrTest,
	testing::Values(
		std::make_tuple(15, 4),
		std::make_tuple(1, 2)
	));


TEST_P(PrimeNumberCalculatorParametrTest, General_Tests)
	{
	size_t expected_number = std::get<1>(GetParam());
	EXPECT_THAT(result, ::testing::Not(::testing::Contains(expected_number)));
	}

template<typename TValue>
std::vector<TValue> GetPrimeNumbersTemplate(size_t i_till_value)
	{
	std::vector<TValue> temp;
	temp.reserve(i_till_value / 3.14);

	if constexpr (std::is_same_v<TValue, int> || std::is_same_v<TValue, double>)
		{
		for (size_t i = 1; i <= i_till_value; i++)
			{
			if (check_is_prime(i))
				{
				temp.emplace_back(i);
				}
			}
		}
	else if constexpr (std::is_same_v<TValue, std::string>)
		{
		for (size_t i = 1; i <= i_till_value; i++)
			{
			if (check_is_prime(i))
				{
				temp.push_back(std::to_string(i));
				}
			}
		}
	else if constexpr (std::is_same_v<TValue, std::wstring>)
		{
		for (size_t i = 1; i <= i_till_value; i++)
			{
			if (check_is_prime(i))
				{
				temp.push_back(std::to_wstring(i));
				}
			}
		}
	return temp;
	}

template<typename TValue>
class PrimeNumberCalculatorTemplate : public ::testing::Test {};

using TestDtypes = ::testing::Types<std::tuple<int, double, std::string, std::wstring>>;
TYPED_TEST_SUITE(PrimeNumberCalculatorTemplate, TestDtypes);

TYPED_TEST(PrimeNumberCalculatorTemplate, HasInt3_When_Till15)
	{
	using A = std::tuple_element<0, decltype(TypeParam())>::type;
	EXPECT_THAT(GetPrimeNumbersTemplate<A>(15), ::testing::Contains(3));
	}

TYPED_TEST(PrimeNumberCalculatorTemplate, HasDouble3_When_Till15)
	{
	using A = std::tuple_element<1, decltype(TypeParam())>::type;
	EXPECT_THAT(GetPrimeNumbersTemplate<A>(15), ::testing::Contains(3.));
	}

TYPED_TEST(PrimeNumberCalculatorTemplate, HasString3_When_Till15)
	{
	using A = std::tuple_element<2, decltype(TypeParam())>::type;
	EXPECT_THAT(GetPrimeNumbersTemplate<A>(15), ::testing::Contains("3"));
	}

TYPED_TEST(PrimeNumberCalculatorTemplate, HasWString3_When_Till15)
	{
	using A = std::tuple_element<3, decltype(TypeParam())>::type;
	EXPECT_THAT(GetPrimeNumbersTemplate<A>(15), ::testing::Contains(L"3"));
	}