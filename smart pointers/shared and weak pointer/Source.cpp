#include <cassert>
#include "shared_pointer.h" 
#include "weak_pointer.h" 
#include <iostream>  
#include <string>  
#include <memory>  


using namespace std;

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

int main()
    {
    // test shared pointer
    //shared_pointer<A> _temp1(new A(5));
    //std::cout << _temp1->get_data() << std::endl;
    //const shared_pointer<A> _temp = std::move(_temp1);

    //std::cout << _temp->get_data() << std::endl;
    //shared_pointer<A> _temp2;
    //_temp2 = _temp;

    //std::cout << _temp->get_data() << std::endl;
    //std::cout << _temp2->get_data() << std::endl;

    //test weak pointer
    shared_pointer<A> shared(new A(10));
    weak_pointer<A> weak(shared);

    std::cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired\n";

    shared.reset();

    std::cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired\n"; 
    return 0;
    }