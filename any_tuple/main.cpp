#include <iostream>
#include "tuple.h"
#include "any.h"
#include <tuple>
#include <vector>
#include <string>
#include <utility> 

void test_tuple()
    {

    tuple<> b;
    tuple<int, double, std::string> c(3, 4., "Lisa Simpson");

    auto t = make_tuple(10, 2);
    //int a, d;
    //tie(a, d) = std::make_tuple(10, 2);
    //std::cout << get<1>(c);
    //auto t = make_tuple(10, 2.);

    }

void test_any()
    {
    any a = 1;
    std::cout << a.type().name() << ": " << any_cast<int>(a) << '\n';

    a = 3.14;
    std::cout << a.type().name() << ": " << any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << any_cast<bool>(a) << '\n';

    // bad cast
    try
        {
        a = 1;
        std::cout << any_cast<float>(a) << '\n';
        }
    catch (const bad_any_cast& e)
        {
        std::cout << e.what() << '\n';
        }

    // has value
    a = 1;
    if (a.has_value())
        {
        std::cout << a.type().name() << '\n';
        }

    // reset
    a.reset();
    if (!a.has_value())
        {
        std::cout << "no value\n";
        }
 }

int main()
	{
    //test_any();
    test_tuple();
    std::cin.get();
	}