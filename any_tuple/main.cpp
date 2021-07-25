#include <iostream>
#include "tuple.h"
#include "any.h"
#include <string>
#include <utility> 
#include <any> 
#include <tuple> 

void test_tuple()
    {

    tuple<> a;
    tuple<int, int, int, double, std::string> c(3, 4, 5, 4., "Lisa Simpson");
    auto t = make_tuple(10, 2);
    int b = 0, d = 0, e = 0;
    tie(b, d, e) = make_tuple(10, 2, 3);
    std::cout << get<4>(c);
    }

void test_any()
    {
    any b = 1.5;
    any c = 1.2;
    c = b;
    std::cout << c.type().name() << ": " << any_cast<double>(c) << '\n';
    std::cout << b.type().name() << ": " << any_cast<double>(b) << '\n';

    b = 3;
    c = std::move(b);
    std::cout << c.type().name() << ": " << any_cast<int>(c) << '\n';

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
    test_any();
    test_tuple();
    std::cin.get();
	}