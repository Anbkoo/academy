#include <iostream>  
#include <string>  
#include <memory> 
#include <type_traits> 

#include "shared_pointer.h" 
#include "weak_pointer.h"
#include "unique_pointer.h"

class A
    {
    private:
        int data = 0;
    public:
        explicit A(int _data) : data(_data) {};

        void set_data(int _data)
            {
            data = _data;
            }

        int get_data()
            {
            return data;
            }


    };

void test_shared_pointer()
    {
    shared_pointer<A> _temp1(new A(5));
    std::cout << _temp1->get_data() << std::endl;
    const shared_pointer<A> _temp = std::move(_temp1);

    std::cout << _temp->get_data() << std::endl;
    shared_pointer<A> _temp2;
    _temp2 = _temp;

    std::cout << _temp->get_data() << std::endl;
    std::cout << _temp2->get_data() << std::endl;

    auto sp = make_shared<A>(12);
    static_assert(std::is_same_v<decltype(sp), shared_pointer<A>>);
    std::cout << sp->get_data() << '\n';
    }

void test_unique_pointer()
    {
    unique_pointer<A> _temp1;
    unique_pointer<A> _temp = std::move(_temp1);
    _temp.reset(nullptr);

    auto sp = make_unique<A>(12);
    static_assert(std::is_same_v<decltype(sp), unique_pointer<A>>);
    std::cout << sp->get_data() << '\n';
    }

void test_weak_pointer()
    {
    shared_pointer<A> shared(new A(10));
    weak_pointer<A> weak(shared);

    std::cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired\n";
    shared.reset();
    std::cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired\n";
    }

int main()
    {
    test_shared_pointer();
    test_unique_pointer();
    std::cin.get();
    return 0;
    }